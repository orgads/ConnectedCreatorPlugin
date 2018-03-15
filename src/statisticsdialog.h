#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>

namespace Ui { class StatisticsDialog; }
namespace KUserFeedback { class Provider; }
class QJsonModel;

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
    void on_textToolButton_toggled(bool checked);
    void on_treeToolButton_toggled(bool checked);

private:
    void init();

    Ui::StatisticsDialog *ui;
    KUserFeedback::Provider *m_feedbackProvider = nullptr;
    QJsonModel *m_model;
    void syncScrollbars();
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // STATISTICSDIALOG_H
