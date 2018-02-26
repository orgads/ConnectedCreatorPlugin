#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>

namespace Ui {
class StatisticsDialog;
}

namespace ConnectedCreator {
namespace Internal {

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = 0);
    ~StatisticsDialog();

private slots:
    void on_textToolButton_clicked(bool checked);
    void on_treeToolButton_clicked(bool checked);

private:
    Ui::StatisticsDialog *ui;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // STATISTICSDIALOG_H
