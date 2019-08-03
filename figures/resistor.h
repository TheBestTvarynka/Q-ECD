#ifndef RESISTOR_H
#define RESISTOR_H

#include "figures/figureinterface.h"

class Resistor : public FigureInterface
{
    float r;
public:
    Resistor(int X, int Y);
    void print(double, PaintBoard *);
    static pair<double, double> Clamp1(double X, double Y) { return pair<double, double>(X + 4, Y); }
    static pair<double, double> Clamp2(double X, double Y) { return pair<double, double>(X - 4, Y); }
};

#endif // RESISTOR_H
