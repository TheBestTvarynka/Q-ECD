#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "figures/figureinterface.h"

class capacitor: public FigureInterface
{
    float c;
public:
    capacitor(int X, int Y);
    void print(double);
    static pair<double, double> Clamp1(double X, double Y) { return pair<double, double>(X + 4, Y); }
    static pair<double, double> Clamp2(double X, double Y) { return pair<double, double>(X - 4, Y); }
};

#endif // CAPACITOR_H
