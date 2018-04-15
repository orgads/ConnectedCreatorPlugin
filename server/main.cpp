#include <httpserver.h>
#include <QDebug>

void receiveAnalytics(qttp::HttpData& data)
{
    // Get and print request
    QJsonDocument doc(data.getRequest().getJson());
    qDebug().noquote() << doc.toJson();

    // Create responce
    QJsonObject& json = data.getResponse().getJson();
    json["Responce"] = "Success";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Always initialize in the main thread.
    qttp::HttpServer* httpSvr = qttp::HttpServer::getInstance();
    httpSvr->initialize();

    // Create an action that will handle all requests
    auto action = httpSvr->createAction(receiveAnalytics);

    // Register the action to handle http GET for the path "/analytics".
    action->registerRoute(qttp::HttpMethod::POST, "/analytics");

    // Libuv runs in its own thread.
    httpSvr->startServer();

    return a.exec();
}
