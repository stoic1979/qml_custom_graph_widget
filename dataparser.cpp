#include "dataparser.h"
#include <QFile>
#include<QDebug>
#include <QUrl>
#include <QDir>
#include "graphitem.h"

DataParser::DataParser(QObject *parent) : QObject(parent)
{}

DataParser::~DataParser()
{}

QVector<GraphItem*>* DataParser:: getvalue(){
    QString path = "/home/wb/work/QtGraphPlot/gradation-SHC-2.grd";
    QFile file(path);

    QVector<GraphItem*> *data = new QVector<GraphItem*>();

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();
            if(line.length() == 0 || line.startsWith('#')) continue;

            QStringList vals = line.split(' ');

            //qDebug() << "line: " << line << " ---- cnt: " << vals.count();
            GraphItem *gi = new GraphItem();
            for(int i=0; i<vals.length(); i++) {
                if(vals.at(i) == "" || vals.at(i) == " ") continue;
                //qDebug() << "i: " << i << " ---- item: " << vals.at(i);
                gi->addElement(vals.at(i).toFloat());
            }
            //gi->log();
            data->append(gi);
        }
        file.close();
    } else {
        qDebug() << "failed to open file";
    }

    return data;

}

QVector<GraphItem*>* DataParser:: getValueRandom(){

    QVector<GraphItem*> *data = new QVector<GraphItem*>();

    for(int t=0; t< 10; t++) {
        GraphItem *gi = new GraphItem();
        for(int i=0; i<5; i++) {
            gi->addElementRandom();
        }
        //gi->log();
        data->append(gi);
    }
    return data;
}




