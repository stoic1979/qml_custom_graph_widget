#include "graphitem.h"
#include <QDebug>

GraphItem::GraphItem(QObject *parent) : QObject(parent), index(0)
{}

GraphItem::~GraphItem()
{}

void GraphItem::addElement(float elem) {
    switch(index) {
    case 0: Perc = elem; break;
    case 1: DO   = elem; break;
    case 2: P1   = elem; break;
    case 3: P2   = elem; break;
    case 4: ETA  = elem; break;
    }

    index ++;
}

void GraphItem::addElementRandom() {
    static double e = 0;

    static double p1 = 1;
    static double p2 = 15;
    static double d = 10;

    static double perc = 5;

    //--------------------------------
    //  Some random data simulation
    //--------------------------------

    switch(index) {
    case 0:
        //Perc = elem;
        perc +=  rand() % 5;
        Perc = perc;
        break;
    case 1:

        //DO   = elem;
        d +=  rand() % 5;
        DO = d;
        break;
    case 2:
        //P1   = elem;
        p1 +=  rand() % 7;
        P1 = p1;
        break;
    case 3:
        //P2   = elem;
        p2 +=  rand() % 6;
        P2 = p2;
        break;
    case 4:
        //ETA  = elem;
        e += 0.01;
        ETA = e;
        break;
    }

    index ++;
}

void GraphItem::log() {
    qDebug()<< " ---- Graph Item ----";
    qDebug()<< "Perc . . . : " << Perc;
    qDebug()<< "DO . . . . : " << DO;
    qDebug()<< "P1 . . . . : " << P1;
    qDebug()<< "P2 . . . . : " << P2;
    qDebug()<< "ETA . .. . : " << ETA;

}
