#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QStringList>
#include <QVector>
#include "graphitem.h"

class DataParser : public QObject
{
    Q_OBJECT

public:
    explicit DataParser(QObject *parent = 0);
    ~DataParser();

      QVector<GraphItem*>* getvalue();
      QVector<GraphItem*>* getValueRandom();

signals:

public slots:

};

#endif // DATAPARSER_H
