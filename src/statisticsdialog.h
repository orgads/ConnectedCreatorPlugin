#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>

namespace Ui { class StatisticsDialog; }
namespace KUserFeedback { class Provider; }

namespace ConnectedCreator {
namespace Internal {

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = 0);
    ~StatisticsDialog();

    void setFeedbackProvider(KUserFeedback::Provider* provider);

protected:
    void  showEvent(QShowEvent *event) override;

private slots:
    void on_textToolButton_clicked(bool checked);
    void on_treeToolButton_clicked(bool checked);

private:
    Ui::StatisticsDialog *ui;
    KUserFeedback::Provider *m_feedbackProvider = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // STATISTICSDIALOG_H
