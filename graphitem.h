#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QObject>

class GraphItem : public QObject
{
    Q_OBJECT
public:
    explicit GraphItem(QObject *parent = 0);
    ~GraphItem();


    inline float getPerc() {return Perc;}
    inline float getDO()   {return DO;}
    inline float getP1()   {return P1;}
    inline float getP2()   {return P2;}
    inline float getETA()  {return ETA;}

    void addElement(float elem);
    void addElementRandom();
    void log();

signals:

public slots:

private:
    float   Perc;
    float   DO;
    float   P1;
    float   P2;
    float   ETA;

    int     index;
};

#endif // GRAPHITEM_H
