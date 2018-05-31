#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QMetaEnum>

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

public slots:
    void embed(bool embedded = true);

protected:
    void  showEvent(QShowEvent *event) override;

private slots:
    void on_textToolButton_toggled(bool checked);
    void on_treeToolButton_toggled(bool checked);
    void on_saveToolButton_clicked();
    void on_clearLogButton_clicked();

    void loadStatistics();

private:
    void init();

    Ui::StatisticsDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
    QJsonModel *m_viewModel;
    void syncScrollbars();
    QByteArray getStatisticsData();
    QMetaEnum telemetryEnum;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // STATISTICSDIALOG_H
