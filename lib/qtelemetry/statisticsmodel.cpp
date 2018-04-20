#include "qtelemetry_logging.h"
#include "qtelemetrymanager.h"
#include "statisticsmodel.h"
#include "statisticsmodel_p.h"

#include <QDir>
#include <QDateTime>
#include <QJsonDocument>

namespace QTelemetry {

StatisticsModel::StatisticsModel(QTelemetryManager *parent)
    : QAbstractListModel(parent)
    , d(new StatisticsModelPrivate(this))
{
    d->manager = parent;
    d->logWatcher.addPath(d->manager->logPath());

    resetTelemetryLevel();
    resetModel();

    connect(d->manager, &QTelemetryManager::dataSubmitted, this,
            &StatisticsModel::resetModel);
    connect(d->manager, SIGNAL(telemetryLevelChanged(TelemetryLevel)),
            this, SLOT(setTelemetryLevel(TelemetryLevel)));
    connect(&d->logWatcher, &QFileSystemWatcher::directoryChanged,
            this, &StatisticsModel::resetModel);
}

StatisticsModelPrivate::StatisticsModelPrivate(StatisticsModel *parent)
    : QObject(parent)
    , q(parent)
{
}

void StatisticsModel::resetModel()
{
    beginResetModel();

    d->items.clear();
    d->items.append("Current telemetry");   // Add first fixed item

    // Get log files list
    QStringList logFilter, list;
    logFilter << "*.log";
    list = QDir(d->manager->logPath())
            .entryList(logFilter, QDir::Files | QDir::Readable, QDir::Name);

    // Add item to model for every file
    foreach (QString file, list) {
        file.chop(4);
        QDateTime dt = QDateTime::fromString(file, "yyyyMMdd-hhmmss");
        if (dt.isValid())
            d->items.append(dt.toString("yyyy-MM-dd hh:mm:ss"));
    }

    endResetModel();
}

QVariant StatisticsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row > rowCount() - 1) return QVariant();

    // Prepare file content
    QJsonDocument content = (role >= JsonRole) ? d->logFileContent(row) : QJsonDocument();
    // TODO: Filter content by telemetry level
    // ...

    switch (role) {
        case Qt::DisplayRole:
            return d->items[row];
        case JsonRole:
            if(row == 0)
                return d->manager->jsonData();
            else
                return content;
        case SubmitTimeRole:
            if(row == 0)
                return QDateTime::currentDateTimeUtc();
            else
                return QDateTime::fromString(d->items[row], "yyyy-MM-dd hh:mm:ss");
        case TransferredRole:
            if(row == 0)
                return false;
            else
                return d->isTransferred(content);
    }
    return QVariant();
}

QJsonDocument StatisticsModelPrivate::logFileContent(int row)
{
    if(row > 0) {
        // Restore correct file name
        QString fileName = QDateTime::fromString(items[row], "yyyy-MM-dd hh:mm:ss")
                .toString("yyyyMMdd-hhmmss") + ".log";
        // Open file
        QFile file(manager->logPath() + "/" + fileName);
        if (!file.open(QFile::ReadOnly)) {
            qCWarning(Log) << tr("Unable to open statistics log file %1: %2.")
                              .arg(fileName, file.errorString());
            return QJsonDocument();
        }
        // Read and return file content
        return QJsonDocument::fromJson(file.readAll());
    }
    return QJsonDocument();
}

bool StatisticsModelPrivate::isTransferred(const QJsonDocument &doc) const
{
    QJsonValue value = doc["submitted"]["transferred"];
    if(value.isUndefined())
        return false;
    else
        return value.toBool();
}

int StatisticsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return d->items.count();
}

void StatisticsModel::setTelemetryLevel(const TelemetryLevel level)
{
    beginResetModel();
    d->level = level;
    endResetModel();
}

void StatisticsModel::resetTelemetryLevel()
{
    beginResetModel();
    d->level = d->manager->telemetryLevel();
    endResetModel();
}

}   // namespace QTelemetry
