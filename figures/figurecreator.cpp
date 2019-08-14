#include "figurecreator.h"

FigureCreator::FigureCreator()
{
    templates[0] = resistor;
    templates[1] = capacitor;
}

FigureInterface *FigureCreator::resistor(int x, int y, QString name, QString value)
{
    FigureInterface *new_figure = new Resistor(x, y, name, value);
    return new_figure;
}

FigureInterface *FigureCreator::capacitor(int x, int y, QString name, QString value)
{
    FigureInterface *new_figure = new Capacitor(x, y, name, value);
    return new_figure;
}
