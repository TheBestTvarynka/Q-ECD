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
    int selected_clamp;
public:
    DataFigures();
    void print(double);
    void add(FigureInterface *);
    void select_figure(QPoint, double);
    void MoveSelectedFigure(FigureInterface *, double, double);
    void RoundCoordinates(FigureInterface *);
    void Register(Cable *, int);
    FigureInterface *GetSelectedFigure();
    pair<QPoint, double> SelectClamp(QPoint, double);
};

#endif // DATAFIGURES_H
