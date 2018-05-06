#include "qtelemetry_logging.h"
#include "qtelemetrymanager.h"
#include "qtelemetrymanager_p.h"
#include "abstractdatasource.h"
#include "statisticsmodel.h"
#include "qtelemetryconstants.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

namespace QTelemetry {

Q_LOGGING_CATEGORY(Log, "io.qt.QTelemetry", QtInfoMsg)

QTelemetryManager::QTelemetryManager(QObject *parent)
    : QObject(parent)
    , d(new QTelemetryManagerPrivate(this))
{
    d->model = new StatisticsModel(this);
}

QTelemetryManager::~QTelemetryManager()
{
    delete d;
}

QTelemetryManagerPrivate::~QTelemetryManagerPrivate()
{
    qDeleteAll(sources);
}

QString QTelemetryManagerPrivate::organization()
{
    QString org =
    #ifdef Q_OS_MAC
        QCoreApplication::organizationDomain().isEmpty()
            ? QCoreApplication::organizationName() : QCoreApplication::organizationDomain();
    #else
        QCoreApplication::organizationName().isEmpty()
            ? QCoreApplication::organizationDomain() : QCoreApplication::organizationName();
    #endif
    if (org.isEmpty())
        org = QLatin1String("Unknown Organization");
    return org;
}

void QTelemetryManagerPrivate::createSettings()
{
    settings = new QSettings(organization(), "QTelemetry." + productId);
}

QSettings *QTelemetryManager::settings() const
{
    return d->settings;
}

void QTelemetryManager::setProductIdentifier(const QString &productId)
{
    d->productId = productId;
    d->createSettings(); // Reload settings

    emit productIdentifierChanged(productId);
}

QString QTelemetryManager::productIdentifier() const
{
    return d->productId;
}

bool QTelemetryManager::isEnabled() const
{
    d->createSettings(); // Update settings

    // Read enable settings
    return d->settings->value("Telemetry/Enabled", false).toBool();;
}

void QTelemetryManager::setEnabled(bool enabled)
{
    if(enabled == isEnabled()) return;

    // Write enable settings
    d->settings->setValue("Telemetry/Enabled", enabled);
    d->settings->sync();
}

void QTelemetryManager::addDataSource(QAbstractDataSource *source)
{
    if(!d->index.contains(source->id())) {
        d->sources.append(source);
        d->index[source->id()] = d->sources.count() - 1;
        source->setManager(this);
    } else {
        int idx = d->index[source->id()];
        if(source != d->sources[idx]) { // If not the same - replace source
            delete d->sources[idx];
            d->sources[idx] = source;
            source->setManager(this);
        }
    }
}

QList<QAbstractDataSource *> QTelemetryManager::dataSources() const
{
    return d->sources;
}

QAbstractDataSource *QTelemetryManager::dataSource(const QString& id) const
{
    if(d->index.contains(id))
        return d->sources[d->index[id]];
    else {
        qCWarning(Log) << "Data source '" << id << "' does not exist!";
        return nullptr;
    }
}

bool QTelemetryManagerPrivate::isValidSource(QAbstractDataSource *source) const
{
    if (source->id().isEmpty()) {
        qCWarning(Log) << "Skipping data source with empty ID!";
        return false;
    }
    if (source->name().isEmpty()) {
        qCWarning(Log) << "Skipping data source with empty name!";
        return false;
    }
    if (source->telemetryLevel() == TelemetryLevel::NoTelemetry) {
        qCWarning(Log) << "Source" << source->id() <<
                          "telemetry level set to NoTelemetry, ignoring!";
        return false;
    }
    if (source->description().isEmpty()) {
        qCWarning(Log) << "Source" << source->id() << "has no description, ignoring!";
        return false;
    }

    Q_ASSERT(!source->name().isEmpty());
    Q_ASSERT(source->telemetryLevel() != TelemetryLevel::NoTelemetry);
    Q_ASSERT(!source->description().isEmpty());
    return true;
}

QJsonDocument QTelemetryManager::jsonData(TelemetryLevel level)
{
    // Separate generic & analytics properties
    QJsonObject complete, environment, analytics;

    if(isEnabled() && level != TelemetryLevel::NoTelemetry)
    {
        foreach(auto source, d->sources)
        {
            if(!d->isValidSource(source) || level < source->telemetryLevel())
                continue;

            // Get data source JSON value
            QJsonValue object;
            QVariant data = source->data();
            if(data.canConvert<QVariantMap>())
                object = QJsonObject::fromVariantMap(data.toMap());
            else if(data.canConvert<QVariantList>())
                object = QJsonArray::fromVariantList(data.value<QVariantList>());
            else {
                qCWarning(Log) << "wrong type for" << source->id() << data;
                continue;
            }

            // Separate properties
            if(source->telemetryLevel() == TelemetryLevel::BasicSystemInformation ||
               source->telemetryLevel() == TelemetryLevel::DetailedSystemInformation)
            {
                environment.insert(source->id(), object);
            } else {
                analytics.insert(source->id(), object);
            }
        }
    }
    // Concatenate properties' scopes in single JSON object
    complete.insert("environment", environment);
    complete.insert("analytics", analytics);
    QJsonDocument doc(complete);

    return doc;
}

QByteArray QTelemetryManager::data(TelemetryLevel level)
{
    // JSON-format statistics generation
    QJsonDocument doc = jsonData(level);
    return doc.toJson();
}

QByteArray QTelemetryManager::data()
{
    return data(telemetryLevel());
}

QJsonDocument QTelemetryManager::jsonData()
{
    return jsonData(telemetryLevel());
}

QByteArray QTelemetryManager::logData(const QDateTime &date)
{
    return ((StatisticsModel *)d->model)->logData(date);
}

QDateTime QTelemetryManager::submit()
{
    QJsonDocument statisticsData = jsonData();

    // Log data to file
    QDateTime submissionTime = d->writeStatistics(statisticsData);

    // Reset in all data sources called automatically here
    emit dataSubmitted(submissionTime);
    return submissionTime;
}

QDateTime QTelemetryManagerPrivate::writeStatistics(const QJsonDocument &data)
{
    QDateTime dt = QDateTime::currentDateTimeUtc();

    // Insert submitted date time to log file
    QJsonObject root = data.object();
    root.insert("submitted",
                QJsonObject({{"time", dt.toString(Constants::ItemDtFormat)}}));
    QJsonDocument doc(root);

    // Get path to store statistics data logs
    QString path = q->logPath();
    QDir().mkpath(path);    // Create dir if not exists

    // Open statistics data log file for writing
    QString fileName = dt.toString(Constants::FileNameDtFormat);
    QFile file(path + "/" + fileName + ".log");
    if (!file.open(QFile::WriteOnly)) {
        qCWarning(Log) << "Unable to open file for statistics:"
                       << file.fileName() << file.errorString();
        return QDateTime();
    }

    // Save statistics data log to file
    file.write(doc.toJson());
    qDebug() << "Statistics log written:" << file.fileName();
    return QDateTime::fromString(fileName, Constants::FileNameDtFormat);
}

QString QTelemetryManager::logPath() const
{
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/telemetry";
}

TelemetryLevel QTelemetryManager::telemetryLevel() const
{
    return d->level;
}

void QTelemetryManager::setTelemetryLevel(const TelemetryLevel level)
{
    d->level = level;
    emit telemetryLevelChanged(d->level);
}

QAbstractItemModel *QTelemetryManager::statisticsModel() const
{
    return d->model;
}

}   // namespace QTelemetry
