#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "figures/figureinterface.h"

class capacitor: public FigureInterface
{
    float c;
public:
    capacitor(int X, int Y);
    void print(double);
    static QPoint Clamp1(int X, int Y) { return QPoint(X + 4, Y); }
    static QPoint Clamp2(int X, int Y) { return QPoint(X - 4, Y); }
};

#endif // CAPACITOR_H
