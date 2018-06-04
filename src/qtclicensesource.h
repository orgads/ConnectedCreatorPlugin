#ifndef QTCLICENSESOURCE_H
#define QTCLICENSESOURCE_H

#include "abstractdatasource.h"

class QtcLicenseSource : public QTelemetry::QAbstractDataSource
{
public:
    QtcLicenseSource();

    QString name() const override;
    QString description() const override;
    QVariant data() final override;

private:
    QString getLicense();

};

#endif // QTCLICENSESOURCE_H
