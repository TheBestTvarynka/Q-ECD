#include "figureinterface.h"

FigureInterface::FigureInterface(int X, int Y)
{
    x = X;
    y = Y;
    main_color[0] = 0.0;
    main_color[1] = 1.0;
    main_color[2] = 0.0;
}

void FigureInterface::SetMainColor(double color[3])
{
    main_color[0] = color[0];
    main_color[1] = color[1];
    main_color[2] = color[2];
}

void FigureInterface::SetPosition(double X, double Y)
{
    x = X; y = Y;
}

void FigureInterface::MoveFigure(double dX, double dY)
{
    x += dX; y += dY;
}
