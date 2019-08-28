#include "figureinterface.h"
#include "view/qtreeitem.h"
#include <QDebug>

FigureInterface::FigureInterface(int X, int Y, int R, QString n, QString v, int t)
{
    rotation = R;
    x = X;
    y = Y;
    main_color[0] = 0.0;
    main_color[1] = 1.0;
    main_color[2] = 0.0;
    name = n;
    value = v;
    type = t;
}

FigureInterface::FigureInterface(const FigureInterface *origin)
{
    *this = *origin;
}

pair<int, double> FigureInterface::SelectClamp(QPoint mouse_pos, double Scale, QMap<int, GetClampCoordinates> clamp_c)
{
    if (clamp_c.size() == 0)
    {
        return pair<int, double>(-1, -1.0);
    }
    pair<double, double> clamp = (*clamp_c[0])(int(x), int(y));
    int best_clamp = 0;
    double min_distance = sqrt(pow((clamp.first) * Scale - mouse_pos.x(), 2) + pow((clamp.second) * Scale - mouse_pos.y(), 2));
    double distance = min_distance;
    for(int i = 1; i < clamp_c.size(); i++)
    {
        clamp = (*clamp_c[i])(int(x), int(y));
        distance = sqrt(pow((clamp.first) * Scale - mouse_pos.x(), 2) + pow((clamp.second) * Scale - mouse_pos.y(), 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            best_clamp = i;
        }
    }
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
    data["TEXT"][0] = *(new QVariant(QPointF(x, y)));
}

void FigureInterface::SetName(QString Name)
{
    name = Name;
    treeItem->setText(0, Name);
}

void FigureInterface::SetValue(QString Value)
{
    value = Value;
    treeItem->setText(1, Value);
}

void FigureInterface::Rotate(double angle)
{
    rotation += angle;
    rotation = rotation % 360;
}

void FigureInterface::DeleteTreeItem()
{
    delete treeItem;
}

pair<double, double> FigureInterface::RotatePoint(pair<double, double> point, double angel)
{
    angel *= M_PI / 180;
    return pair<double, double>(cos(angel) * (point.first - x) - sin(angel) * (point.second - y) + x, sin(angel) * (point.first - x) + cos(angel) * (point.second - y) + y);
}

void FigureInterface::MoveFigure(double dX, double dY)
{
    x += dX; y += dY;
    data["TEXT"][0] = *(new QVariant(QPointF(x, y)));
    Notify();
}

void FigureInterface::Notify()
{
    pair<double, double> clamp;
    QMapIterator<IObserver*, int> it(connections);
    while (it.hasNext())
    {
        it.next();
        clamp = this->GetClamp(it.value());
        it.key()->update(this, clamp.first, clamp.second);
    }
}
