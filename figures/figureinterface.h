#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include "figures/iobservable.h"

class FigureInterface : public IObservable
{
protected:
    double x, y;
public:
    FigureInterface() : x(10.0), y(10.0) {}
    FigureInterface(int X, int Y);
    virtual void print(double) = 0;
};

#endif // FIGUREINTERFACE_H
