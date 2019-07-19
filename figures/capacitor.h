#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "figures/figureinterface.h"

class capacitor: public FigureInterface
{
    float c;
public:
    capacitor() : c(1) {}
    void print(double);
};

#endif // CAPACITOR_H
