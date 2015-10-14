#include "graphwidget.h"

#import <QPalette>

GraphWidget::GraphWidget(QDeclarativeItem *parent)
    : QDeclarativeItem(parent){

    // need to disable this flag to draw inside a QDeclarativeItem
    setFlag(QGraphicsItem::ItemHasNoContents, false);

    customPlot = new QCustomPlot();

    // needed proxy widget to plot graph on declarative item
    proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(customPlot);

    consumerThread = new ConsumerThread();
    customPlot->setBackground(Qt::black);
    customPlot->xAxis->setBasePen(QPen(Qt::cyan));
    customPlot->xAxis->setLabelColor(Qt::cyan);
    customPlot->xAxis->setLabel("ETA");
    customPlot->xAxis->setTickLabelColor(Qt::cyan);

    customPlot->yAxis->setLabelColor(Qt::cyan);
    customPlot->yAxis->setLabel("y-axis");
    customPlot->yAxis->setBasePen(QPen(Qt::cyan));
    customPlot->yAxis->setTickLabelColor(Qt::cyan);

    connect(consumerThread, &ConsumerThread::resultReady, this, &GraphWidget::handleResults);
    //connect(consumerThread, &ConsumerThread::finished, consumerThread, &QObject::deleteLater);

    consumerThread->start();

}

GraphWidget::~GraphWidget(){
    delete customPlot;
    delete proxyWidget;
}

QColor GraphWidget::color() const {
    return m_color;
}

void GraphWidget::setColor(const QColor &color)
{
    m_color = color;
}

void GraphWidget::handleResults(QVector<GraphItem*> *data) {
    plotData(data);
}

void GraphWidget::plotData(QVector<GraphItem*> *data)
{
    qDebug()<< "Got graph data to plot....";

    int removeCnt = customPlot->clearGraphs();
    qDebug()<< " removeCnt=" << removeCnt;

    customPlot->replot( QCustomPlot::rpHint	);

    // adding 4 new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::yellow));

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::green));
    customPlot->graph(2)->setBrush(QBrush(QColor(0, 255, 0, 20)));

    customPlot->addGraph();
    customPlot->graph(3)->setPen( QPen( QColor(255, 255, 255) ) );
    customPlot->graph(2)->setBrush(QBrush(QColor(255, 255, 255, 20)));

    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(data->length()), y0(data->length()), y1(data->length()), y2(data->length()), y3(data->length());

    static double t = 0;
    double step = .1;

    for(int i=0; i<data->length(); i++) {
        GraphItem *gi = data->at(i);
        //gi->log();
        //x[i]  = gi->getETA();
        t += step;
        x[i] = t;
        y0[i] = gi->getPerc();
        y1[i] = gi->getDO();
        y2[i] = gi->getP1();
        y3[i] = gi->getP2();
    }


    customPlot->xAxis->setRange(x[0], x[data->length()-1], Qt::AlignRight);
    // configuring right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    // making left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // passing data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    customPlot->graph(2)->setData(x, y2);
    customPlot->graph(3)->setData(x, y3);

    customPlot->graph(1)->setLineStyle(QCPGraph::lsStepCenter);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):

    customPlot->graph(0)->rescaleAxes();
    customPlot->graph(1)->rescaleAxes(true);
    customPlot->graph(2)->rescaleAxes(true);
    customPlot->graph(3)->rescaleAxes(true);

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MrealtimeDataSlot:
    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    //dataTimer.start(2000); // Interval 0 means to refresh as fast as possible

    customPlot->replot( QCustomPlot::rpHint	);
}

void GraphWidget::realtimeDataSlot()
{
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange(key+0.05, 50, Qt::AlignRight);
  //customPlot->replot();
}

void GraphWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget)
{
    proxyWidget->resize(width(), height());
}

