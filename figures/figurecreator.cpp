#include "figurecreator.h"

FigureCreator::FigureCreator()
{
    templates[0] = resistor;
    templates[1] = capacitor;
}

FigureInterface *FigureCreator::resistor(int x, int y, int r, QString name, QString value, int type)
{
    FigureInterface *new_figure = new Resistor(x, y, r, name, value, type);
    return new_figure;
}

FigureInterface *FigureCreator::capacitor(int x, int y, int r, QString name, QString value, int type)
{
    FigureInterface *new_figure = new Capacitor(x, y, r, name, value, type);
    return new_figure;
}
