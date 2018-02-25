#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"

StatisticsDialog::StatisticsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::on_textToolButton_clicked(bool checked)
{
    if(checked)
        ui->textBrowser->hide();
    else
        ui->textBrowser->show();
}

void StatisticsDialog::on_treeToolButton_clicked(bool checked)
{
    if(checked)
        ui->treeWidget->hide();
    else
        ui->treeWidget->show();
}
