#include <QtTest>
#include <QCoreApplication>

#include "qscheduler.h"
#include "qtelemetrymanager.h"

class QTelemetryTest : public QObject
{
    Q_OBJECT

public:
    QTelemetryTest();
    ~QTelemetryTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void scheduler_test_case1();

private:
    QTelemetry::QTelemetryManager *m_manager = nullptr;
    QTelemetry::QScheduler *m_scheduler = nullptr;
};

QTelemetryTest::QTelemetryTest()
{

}

QTelemetryTest::~QTelemetryTest()
{

}

void QTelemetryTest::initTestCase()
{
    m_manager = new QTelemetry::QTelemetryManager(this);
    m_manager->setProductIdentifier("io.qt.qtc.analytics");
    m_scheduler = new QTelemetry::QScheduler(m_manager->settings(), this);
}

void QTelemetryTest::cleanupTestCase()
{
    // Delete members
    delete m_scheduler; // Delete scheduler first as manager contains settings
    delete m_manager;
}

void QTelemetryTest::scheduler_test_case1()
{
    qDebug() << QDateTime::currentDateTime().toString(Qt::ISODate) << ": Started ...";
    m_scheduler->addTask("TestTask", [=]() {
        qDebug() << QDateTime::currentDateTime().toString(Qt::ISODate) << ": TestTask executed...";
    }, 7, QTelemetry::DurationMeasure::Minutes);

    m_scheduler->addTask("TestTask2", [=]() {
        qDebug() << QDateTime::currentDateTime().toString(Qt::ISODate) << ": TestTask2 executed...";
    }, 5, QTelemetry::DurationMeasure::Minutes);

    //QObject().thread()->sleep(60*12);
}

QTEST_MAIN(QTelemetryTest)

#include "tst_qtelemetrytest.moc"
