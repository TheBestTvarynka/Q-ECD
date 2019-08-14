#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "figures/figureinterface.h"

class Capacitor: public FigureInterface
{
    float c;
public:
    Capacitor(int X, int Y, QString, QString);
    void print(double, PaintBoard *);
    static pair<double, double> Clamp1(double X, double Y) { return pair<double, double>(X + 4, Y); }
    static pair<double, double> Clamp2(double X, double Y) { return pair<double, double>(X - 4, Y); }
};

#endif // CAPACITOR_H
