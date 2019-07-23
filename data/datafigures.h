#ifndef DATAFIGURES_H
#define DATAFIGURES_H

#include <QVector>
#include <math.h>
#include "figures/figureinterface.h"
#include "figures/resistor.h"
#include "figures/capacitor.h"

class DataFigures
{
    QVector<FigureInterface *> figures;
    FigureInterface *selected_figure;
public:
    DataFigures();
    void print(double);
    void add(FigureInterface *);
    void select_figure(QPoint, double);
    void MoveSelectedFigure(FigureInterface *, double, double);
    FigureInterface *GetSelectedFigure();
    void RoundCoordinates(FigureInterface *);
    // temporary function
    QPoint SelectClamp(QPoint);
};

#endif // DATAFIGURES_H
