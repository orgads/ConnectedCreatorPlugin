#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include "qtelemetry_global.h"

#include <QAbstractListModel>

namespace QTelemetry {

class QTelemetryManager;
class StatisticsModelPrivate;

///
/// \brief The StatisticsModel class
///
class StatisticsModel : public QAbstractListModel
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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    StatisticsModelPrivate *d;
};

}   // namespace QTelemetry

#endif // STATISTICSMODEL_H
