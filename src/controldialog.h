#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>

namespace Ui         { class ControlDialog; }
namespace QTelemetry { class QTelemetryManager; }

namespace ConnectedCreator {
namespace Internal {

class ControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlDialog(QWidget *parent = 0);
    ~ControlDialog();

    void setTelemetryManager(QTelemetry::QTelemetryManager* manager);

public slots:
    void accept() override;

private slots:
    void on_telemetryButton_clicked();
    void goSecondPage();

private:
    void init();
    bool checkEvalLicense();
    void generateDataSourcesList();

    Ui::ControlDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // CONTROLDIALOG_H
