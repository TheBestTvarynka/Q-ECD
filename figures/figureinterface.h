#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include "figures/iobservable.h"

class FigureInterface : public IObservable
{
protected:
    int x, y;
public:
    FigureInterface(int X, int Y);
    virtual void print();
};

#endif // FIGUREINTERFACE_H
