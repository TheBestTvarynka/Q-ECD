#ifndef DATAFIGURES_H
#define DATAFIGURES_H

#include <QVector>
#include <math.h>
#include "cables/iobserver.h"
#include "figures/figureinterface.h"
#include "figures/resistor.h"
#include "figures/capacitor.h"

class PaintBoard;

class DataFigures
{
    QVector<FigureInterface *> figures;
    FigureInterface *selected_figure;
    int selected_clamp;
public:
    DataFigures();
    void print(double, PaintBoard *);
    void add(FigureInterface *);
    QList<IObserver *> erase(FigureInterface *);
    void select_figure(QPoint, double);
    void MoveSelectedFigure(FigureInterface *, double, double);
    void RoundCoordinates(FigureInterface *);
    void Register(FigureInterface *, int, IObserver *, int);
    FigureInterface *GetSelectedFigure();
    QVector<FigureInterface *> GetFigures() { return figures; }
    pair<QPoint, double> SelectClamp(QPoint, double, FigureInterface *&, int &);
    int size() { return figures.size(); }
    void SetSelectedFigure(FigureInterface *);
};

#endif // DATAFIGURES_H
