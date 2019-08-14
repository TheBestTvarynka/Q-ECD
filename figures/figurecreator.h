#ifndef FIGURECREATOR_H
#define FIGURECREATOR_H

#include "figures/resistor.h"
#include "figures/capacitor.h"

typedef FigureInterface* (*NewFigure)(int, int, QString, QString);

class FigureCreator
{
    QMap<int, NewFigure> templates;
public:
    FigureCreator();
    static FigureInterface* resistor(int x, int y, QString name, QString value);
    static FigureInterface* capacitor(int x, int y, QString name, QString value);
    FigureInterface* GetNewFigure(int i, int x, int y, QString name, QString value) { return templates[i](x, y, name, value); }
};

#endif // FIGURECREATOR_H
