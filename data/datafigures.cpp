#include "datafigures.h"

DataFigures::DataFigures()
{
    FigureInterface *tmp = new Resistor;
    figures.push_back(tmp);
}

void DataFigures::print(double Scale)
{
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->print(Scale);
    }
}
