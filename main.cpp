#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDeclarativeView>
#include <QWidget>
#include <QVBoxLayout>
#include <QtDeclarative>

#include "graphwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<GraphWidget,1>("GraphModule", 1, 1, "GraphWidget");

    QDeclarativeView *qmlView = new QDeclarativeView;
    qmlView->setSource(QUrl("qrc:/GraphDemo.qml"));

    qmlView->show();

    return app.exec();
}
