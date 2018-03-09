#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>

namespace Ui            { class ControlDialog; }
namespace KUserFeedback { class Provider; }

namespace ConnectedCreator {
namespace Internal {

class ControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlDialog(QWidget *parent = 0);
    ~ControlDialog();

    void setFeedbackProvider(KUserFeedback::Provider* provider);

public slots:
    void accept() override;

private slots:
    void on_telemetryButton_clicked();
    void goSecondPage();

private:
    void init();
    bool checkEvalLicense();

    Ui::ControlDialog *ui;
    KUserFeedback::Provider *m_feedbackProvider = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // CONTROLDIALOG_H
