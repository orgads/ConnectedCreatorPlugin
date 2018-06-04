#ifndef DATASOURCESDIALOG_H
#define DATASOURCESDIALOG_H

#include <QDialog>

namespace Ui         { class DataSourcesDialog; }
namespace QTelemetry { class QTelemetryManager; }

namespace ConnectedCreator {
namespace Internal {

class DataSourcesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataSourcesDialog(QWidget *parent = 0);
    ~DataSourcesDialog();

    void setTelemetryManager(QTelemetry::QTelemetryManager* manager);

public slots:
    void embed(bool embedded = true);

private:
    void generateDataSourcesList();

    Ui::DataSourcesDialog *ui;
    QTelemetry::QTelemetryManager *m_manager = nullptr;
};

} // namespace Internal
} // namespace ConnectedCreatorPlugin

#endif // DATASOURCESDIALOG_H
