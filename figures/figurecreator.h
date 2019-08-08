#ifndef FIGURECREATOR_H
#define FIGURECREATOR_H

#include "figures/resistor.h"
#include "figures/capacitor.h"

typedef FigureInterface* (*NewFigure)(int, int, QString);

class FigureCreator
{
    QMap<int, NewFigure> templates;
public:
    FigureCreator();
    static FigureInterface* resistor(int x, int y, QString name);
    static FigureInterface* capacitor(int x, int y, QString name);
    FigureInterface* GetNewFigure(int i, int x, int y, QString name) { return templates[i](x, y, name); }
};

#endif // FIGURECREATOR_H
