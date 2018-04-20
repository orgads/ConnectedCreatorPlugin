#include <QtTest>
#include <QCoreApplication>
#include <QJsonDocument>

#include "qscheduler.h"
#include "qtelemetrymanager.h"
#include "statisticsmodel.h"
#include "statisticsmodel_p.h"

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
    void statisticsModel_test_case1();

private:
    QTelemetry::QTelemetryManager *m_manager = nullptr;
    QTelemetry::QScheduler *m_scheduler = nullptr;
    QTelemetry::StatisticsModel *m_model = nullptr;
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
    m_model = new QTelemetry::StatisticsModel(m_manager);
}

void QTelemetryTest::cleanupTestCase()
{
    // Delete members
    delete m_model;
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

void QTelemetryTest::statisticsModel_test_case1()
{
    // Test private StatisticsModel methods
    QTelemetry::StatisticsModelPrivate *stat_p =
            new QTelemetry::StatisticsModelPrivate(m_model);

    // Test on empty JSON
    QJsonDocument doc = QJsonDocument::fromJson(QString("{}").toUtf8());
    Q_ASSERT(!stat_p->isTransferred(doc));

    // Test on JSON with submitted object
    doc = QJsonDocument::fromJson(QString("{\"submitted\":{}}").toUtf8());
    qDebug().noquote() << doc.toJson() << doc.isEmpty();
    Q_ASSERT(!stat_p->isTransferred(doc));

    // Test on JSON with submitted object and transferred value
    doc = QJsonDocument::fromJson(QString("{\"submitted\":{\"transferred\": true}}").toUtf8());
    qDebug().noquote() << doc.toJson();
    Q_ASSERT(stat_p->isTransferred(doc));
}

QTEST_MAIN(QTelemetryTest)

#include "tst_qtelemetrytest.moc"
