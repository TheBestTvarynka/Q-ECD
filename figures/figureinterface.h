#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QGLWidget>
#include "figures/iobservable.h"

class FigureInterface : public IObservable
{
protected:
    int x, y;
public:
    FigureInterface() : x(0), y(0) {}
    FigureInterface(int X, int Y);
    virtual void print() = 0;
};

#endif // FIGUREINTERFACE_H
