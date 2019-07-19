#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "figures/figureinterface.h"

class capacitor: public FigureInterface
{
    float c;
public:
    capacitor() : c(1) {}
    capacitor(int X, int Y) : FigureInterface(X, Y) {}
    void print(double);
};

#endif // CAPACITOR_H
