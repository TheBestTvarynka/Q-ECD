#ifndef DATAFIGURES_H
#define DATAFIGURES_H

#include <QVector>
#include "figures/figureinterface.h"
#include "figures/resistor.h"

class DataFigures
{
    QVector<FigureInterface *> figures;
public:
    DataFigures();
    void print(double);
};

#endif // DATAFIGURES_H
