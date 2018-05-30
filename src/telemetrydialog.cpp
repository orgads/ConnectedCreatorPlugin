#include "telemetrydialog.h"
#include "ui_telemetrydialog.h"

#include <QKeyEvent>

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
    // Filter out Esc key
    ui->settingsPage->installEventFilter(this);
    ui->dataSourcesPage->installEventFilter(this);
    ui->statisticsPage->installEventFilter(this);
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

bool TelemetryDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Escape) {
            // Propagate to parent
            reject();
            return true;
        }  else {
            return false;
        }
    }

    // Standard event processing
    return QObject::eventFilter(obj, event);
}

} // namespace Internal
} // namespace ConnectedCreatorPlugin
