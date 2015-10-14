#include "consumerthread.h"
#include "dataparser.h"

void ConsumerThread::run() {

    while(1) {
        qDebug() << "-- Running Consumer Thread...";

        sleep(2);

        parseData();

    }
}

void ConsumerThread::parseData() {

    DataParser parser;

    // data from file
    //QVector<GraphItem*>* data = parser.getvalue();

    // random data
    QVector<GraphItem*>* data = parser.getValueRandom();

    // after parsing data, emit the result
    emit resultReady(data);
}
