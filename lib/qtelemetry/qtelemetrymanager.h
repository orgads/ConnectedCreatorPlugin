#ifndef QTELEMETRYMANAGER_H
#define QTELEMETRYMANAGER_H

#include "qtelemetry_global.h"

#include <QObject>
#include <QList>

class QSettings;
class QAbstractItemModel;

namespace QTelemetry {

Q_NAMESPACE

class QTelemetryManagerPrivate;
class QAbstractDataSource;

enum class TelemetryLevel {
    NoTelemetry = 0x0,                  ///< Transmit no data at all.
    BasicSystemInformation = 1 << 1,    ///< Transmit basic information about the system.
    BasicUsageStatistics = 1 << 2,      ///< Transmit basic usage statistics.
    DetailedSystemInformation = 1 << 3, ///< Transmit detailed system information.
    DetailedUsageStatistics = 1 << 4,   ///< Transmit detailed (application specific) usage statistics.
};

Q_ENUM_NS(TelemetryLevel)

class QTELEMETRYSHARED_EXPORT QTelemetryManager : public QObject
{
    Q_OBJECT

public:
    QTelemetryManager(QObject *parent = nullptr);
    ~QTelemetryManager();

    /// Adds a data source for telemetry data collection.
    /// @param source The data source to add. The Manager takes ownership of @p source.
    void addDataSource(QAbstractDataSource *source);

    /// Returns all data sources that have been added to this manager.
    /// @see addDataSource
    QList<QAbstractDataSource *> dataSources() const;

    /// Returns data source for given @p id
    QAbstractDataSource *dataSource(const QString& id) const;

    /// Current statistics data as QByteArray
    QByteArray data(TelemetryLevel level);
    /// Current statistics data as QJsonDocument
    QJsonDocument jsonData(TelemetryLevel level);

    /// Current statistics data as QByteArray (overloaded: current telemetry level used)
    QByteArray data();
    /// Current statistics data as QJsonDocument (overloaded: current telemetry level used)
    QJsonDocument jsonData();

    /// Submitted statistics log files storage path
    QString logPath() const;

    /// Returns whether telemetry functionality is enabled on this system.
    bool isEnabled() const;
    /// Set the global (user-wide) activation state for telemetry functionality
    /// @see isEnabled
    void setEnabled(bool enabled);

    /// Returns the current product identifier
    QString productIdentifier() const;
    /// Set the product identifier.
    /// This is used to distinguish independent products on the same server.
    /// If this is not specified, the product identifier is dervied from the application name
    /// organisation domain specified in QCoreApplication.
    void setProductIdentifier(const QString &productId);

    /// Returns global QTelemetry settings object
    QSettings *settings() const;

    /// Returns current telemetry level @see setTelemetryLevel
    TelemetryLevel telemetryLevel() const;
    /// Sets current telemetry level @see telemetryLevel
    void setTelemetryLevel(const TelemetryLevel level);

    /// Statistics log model for current telemetry and archived logs
    /// see @StatisticsModel
    QAbstractItemModel *statisticsModel() const;

public slots:
    /// Submits (returns) current telemetry data and resets all data sources
    QByteArray submit();

signals:
    /// Emitted after data submission
    void dataSubmitted(const QJsonDocument &);
    /// Emitted Product Identifier was changed
    void productIdentifierChanged(QString);
    /// Emitted when Telemetry Level changed
    void telemetryLevelChanged(const TelemetryLevel level);

private:
    QTelemetryManagerPrivate *d;
};

}   // namespace QTelemetry

#endif // QTELEMETRYMANAGER_H
