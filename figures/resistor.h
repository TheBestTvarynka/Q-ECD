#ifndef RESISTOR_H
#define RESISTOR_H

#include "figures/figureinterface.h"

class Resistor : public FigureInterface
{
    float r;
public:
    Resistor() : r(1) {}
    void print(double);
};

#endif // RESISTOR_H
