#ifndef QTELEMETRYMANAGER_H
#define QTELEMETRYMANAGER_H

#include "qtelemetry_global.h"

#include <QObject>
#include <QList>

namespace QTelemetry {

class QTelemetryManagerPrivate;
class AbstractDataSource;

enum class TelemetryLevel {
    NoTelemetry = 0x0, ///< Transmit no data at all.
    BasicSystemInformation = 1 << 1, ///< Transmit basic information about the system.
    DetailedSystemInformation = 1 << 2, ///< Transmit detailed system information.
    DetailedUsageStatistics = 1 << 3, ///< Transmit detailed usage statistics.
};

class QTELEMETRYSHARED_EXPORT QTelemetryManager : public QObject
{
    Q_OBJECT

public:
    Q_ENUM(TelemetryLevel)

    QTelemetryManager(QObject *parent = nullptr);
    ~QTelemetryManager();

    /// Adds a data source for telemetry data collection.
    /// @param source The data source to add. The Manager takes ownership of @p source.
    void addDataSource(AbstractDataSource *source);

    /// Returns all data sources that have been added to this manager.
    /// @see addDataSource
    QList<AbstractDataSource *> dataSources();

    /// Returns data source for given @p id
    AbstractDataSource *dataSource(QString id) const;

    /// Current statistics data
    QByteArray jsonData(TelemetryLevel level);

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

private:
    QTelemetryManagerPrivate *d;
};

}   // namespace QTelemetry

#endif // QTELEMETRYMANAGER_H
