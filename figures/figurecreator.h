#ifndef FIGURECREATOR_H
#define FIGURECREATOR_H

#include "figures/resistor.h"
#include "figures/capacitor.h"

typedef FigureInterface* (*NewFigure)(int, int, int, QString, QString, int);

class FigureCreator
{
    QMap<int, NewFigure> templates;
public:
    FigureCreator();
    static FigureInterface* resistor(int x, int y, int r, QString name, QString value, int type);
    static FigureInterface* capacitor(int x, int y, int r, QString name, QString value, int type);
    FigureInterface* GetNewFigure(int i, int x, int y, int r, QString name, QString value) { return templates[i](x, y, r, name, value, i); }
};

#endif // FIGURECREATOR_H
