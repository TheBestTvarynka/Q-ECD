#ifndef RESISTOR_H
#define RESISTOR_H

#include "figures/figureinterface.h"

class Resistor : public FigureInterface
{
    float r;
public:
    Resistor(int X, int Y);
    void print(double);
    static QPoint Clamp1(int X, int Y) { return QPoint(X + 4, Y); }
    static QPoint Clamp2(int X, int Y) { return QPoint(X - 4, Y); }
};

#endif // RESISTOR_H
