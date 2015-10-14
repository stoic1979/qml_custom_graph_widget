#ifndef CONSUMERTHREAD_H
#define CONSUMERTHREAD_H

#include <QThread>
#include <QtGlobal>
#include <QVector>
#include <QDebug>

#include "graphitem.h"

class ConsumerThread : public QThread
{
    Q_OBJECT

public:
    void run() Q_DECL_OVERRIDE;

private:
    void parseData();

signals:
    void resultReady(QVector<GraphItem*>* data);

};
#endif // CONSUMERTHREAD_H
