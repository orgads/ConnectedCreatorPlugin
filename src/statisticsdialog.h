#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>

namespace Ui { class StatisticsDialog; }
namespace QTelemetry { class QTelemetryManager; }
class QJsonModel;

namespace ConnectedCreator {
namespace Internal {

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = 0);
    ~StatisticsDialog();

    void setTelemetryManager(QTelemetry::QTelemetryManager* manager);

protected:
    void  showEvent(QShowEvent *event) override;

private slots:
    void on_textToolButton_toggled(bool checked);
    void on_treeToolButton_toggled(bool checked);
    void on_saveToolButton_clicked();

    void loadStatistics();

private:
    void init();

    Ui::StatisticsDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
    QJsonModel *m_model;
    void syncScrollbars();
    QByteArray getStatisticsData();
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // STATISTICSDIALOG_H
