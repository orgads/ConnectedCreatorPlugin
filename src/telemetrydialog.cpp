#include "telemetrydialog.h"
#include "ui_telemetrydialog.h"


namespace ConnectedCreator {
namespace Internal {

TelemetryDialog::TelemetryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelemetryDialog)
{
    ui->setupUi(this);

    // Embed dialog as a simple widget
    ui->settingsPage->setWindowFlags(Qt::Widget);
    ui->dataSourcesPage->setWindowFlags(Qt::Widget);
    ui->statisticsPage->setWindowFlags(Qt::Widget);

    // Hide embed dialogs button boxes
    ui->settingsPage->embed();
    ui->dataSourcesPage->embed();
    ui->statisticsPage->embed();
}

TelemetryDialog::~TelemetryDialog()
{
    delete ui;
}

void TelemetryDialog::setTelemetryManager(QTelemetry::QTelemetryManager* manager)
{
    m_manager = manager;

    ui->settingsPage->setTelemetryManager(manager);
    ui->dataSourcesPage->setTelemetryManager(manager);
    ui->statisticsPage->setTelemetryManager(manager);
}

void TelemetryDialog::accept()
{
    ui->settingsPage->accept();

    QDialog::accept();
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
