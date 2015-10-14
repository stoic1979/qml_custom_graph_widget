#ifndef GraphWidget_H
#define GraphWidget_H

#include <QVector>
#include <QDeclarativeItem>
#include <QWidget>
#include <QColor>
#import <QGraphicsProxyWidget>
#import <QTimer>


#include "qcustomplot.h"
#include "consumerthread.h"
#include "graphitem.h"

class GraphWidget : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)


public:
    GraphWidget(QDeclarativeItem *parent = 0);
    ~GraphWidget();

    void plotData(QVector<GraphItem*> *data);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public slots:
    void handleResults(QVector<GraphItem*> *data);
    void realtimeDataSlot();

private:

    QColor                       m_color;
    QCustomPlot                 *customPlot;
    QGraphicsProxyWidget        *proxyWidget;
    QTimer                       dataTimer;

    /*
     * consumer thread to read data preriodically from
     * csv file and update the graph widget
     */
    ConsumerThread              *consumerThread;
};

#endif // GraphWidget_H
