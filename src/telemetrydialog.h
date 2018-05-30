#ifndef TELEMETRYDIALOG_H
#define TELEMETRYDIALOG_H

#include <QDialog>

namespace Ui { class TelemetryDialog; }
namespace QTelemetry { class QTelemetryManager; }

namespace ConnectedCreator {
namespace Internal {

class TelemetryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TelemetryDialog(QWidget *parent = 0);
    ~TelemetryDialog();

    void setTelemetryManager(QTelemetry::QTelemetryManager* manager);

public slots:
    void accept() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::TelemetryDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // TELEMETRYDIALOG_H
