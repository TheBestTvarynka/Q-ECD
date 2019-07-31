#ifndef DATAFIGURES_H
#define DATAFIGURES_H

#include <QVector>
#include <math.h>
#include "cables/iobserver.h"
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
    void Register(FigureInterface *, int, IObserver *, int);
    FigureInterface *GetSelectedFigure();
    pair<QPoint, double> SelectClamp(QPoint, double, FigureInterface *&, int &);
};

#endif // DATAFIGURES_H
