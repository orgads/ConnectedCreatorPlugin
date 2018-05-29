#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui { class SettingsDialog; }
namespace QTelemetry { class QTelemetryManager; }

namespace ConnectedCreator {
namespace Internal {

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void setTelemetryManager(QTelemetry::QTelemetryManager* manager);

public slots:
    void accept() override;
    void embed(bool embedded = true);

private slots:
    void on_timeRadioButton_toggled(bool checked);

private:
    Ui::SettingsDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // SETTINGSDIALOG_H
