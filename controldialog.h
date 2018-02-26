#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class ControlDialog;
}

namespace ConnectedCreator {
namespace Internal {

class ControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlDialog(QWidget *parent = 0);
    ~ControlDialog();

private:
    bool checkEvalLicense();
    bool firstRun();

    Ui::ControlDialog *ui;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // CONTROLDIALOG_H
