#include "figureinterface.h"
#include <QDebug>

FigureInterface::FigureInterface(int X, int Y)
{
    x = X;
    y = Y;
    main_color[0] = 0.0;
    main_color[1] = 1.0;
    main_color[2] = 0.0;
}

pair<int, double> FigureInterface::SelectClamp(QPoint mouse_pos, double Scale, QMap<int, GetClampCoordinates> clamp_c)
{
    if (clamp_c.size() == 0)
    {
        return pair<int, double>(-1, -1.0);
    }
    QPoint clamp = (*clamp_c[0])(int(x), int(y));
    int best_clamp = 0;
    double min_distance = sqrt(pow((clamp.x()) * Scale - mouse_pos.x(), 2) + pow((clamp.y()) * Scale - mouse_pos.y(), 2));
    double distance = min_distance;
    for(int i = 1; i < clamp_c.size(); i++)
    {
        clamp = (*clamp_c[i])(int(x), int(y));
        distance = sqrt(pow((clamp.x()) * Scale - mouse_pos.x(), 2) + pow((clamp.y()) * Scale - mouse_pos.y(), 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            best_clamp = i;
        }
    }
//    if (abs(min_distance) > Scale * 2)
//    {
//        qDebug() << "in emergexit";
//        return pair<int, double>(-1, -1.0);
//    }
    return pair<int, double>(best_clamp, min_distance);
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
