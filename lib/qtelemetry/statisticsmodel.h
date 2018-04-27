#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include "qtelemetry_global.h"

#include <QAbstractListModel>

namespace QTelemetry {

class QTelemetryManager;
class StatisticsModelPrivate;

/// \brief The StatisticsModel class represents model which contains data -
/// statistics logs list with current telemetry item and respective JSON data.
/// This model could be utilized by UI controls like combo boxes, text browsers,
/// JSON treeviews, etc and by service classes like QScheduler,  QNetworkManager
/// to send left behind data to backend.
///
class QTELEMETRYSHARED_EXPORT StatisticsModel : public QAbstractListModel
{
public:
    enum StatisticsRole {
        JsonRole = Qt::UserRole,    /// Current statistics of log file content as QJsonDocument
        SubmitTimeRole,             /// Submited QDateTime
        TransferredRole             /// Successfully or not transferred over network - bool
    };

    StatisticsModel(QTelemetryManager *parent);

public slots:
    /// Reloads model from disk
    void resetModel();

    /// Returns the number of logs stored on a disk + 1 for current data.
    /// When the parent is valid returns 0 (QAbstractListModel).
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    ///< For Qt::DisplayRole returns time string itemsfor every log
    ///< For JsonRole returns statistics JSON log for current or archived telemetry
    ///< For SubmitTimeRole returns submission time
    ///< For TransferredRole returns whether log was transferred to backend true/false
    ///< Otherwise returns QVariant()
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Returns current telemetry level for the model @see setTelemetryLevel
    TelemetryLevel telemetryLevel() const;
    /// Sets current telemetry level for the model @see telemetryLevel
    void setTelemetryLevel(const TelemetryLevel level);

    /// Resets current telemetry level to telemetry manager's level @see telemetryLevel
    void resetTelemetryLevel();

private:
    StatisticsModelPrivate *d;
};

}   // namespace QTelemetry

#endif // STATISTICSMODEL_H
