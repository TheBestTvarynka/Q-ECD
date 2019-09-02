#include "figureinterface.h"
#include "view/qtreeitem.h"
#include <QDebug>

FigureInterface::FigureInterface(int X, int Y, int R, QString n, QString v, int t)
{
    rotation = R;
    x = X;
    y = Y;
    main_color.setRgb(0, 0, 255);
    name = n;
    value = v;
    type = t;
}

FigureInterface::FigureInterface(const FigureInterface *origin)
{
    *this = *origin;
}

pair<int, double> FigureInterface::SelectClamp(QPoint mouse_pos, double Scale)
{
    if (clamp.size() == 0)
    {
        qDebug() << "wfffwfooosssh";
        return pair<int, double>(-1, -1.0);
    }
    int best_clamp = -1;
    QPointF cur_clamp;
    double dis, min_dis = Scale * 3;
    auto determine_dis = [&] () {
        return sqrt( pow(cur_clamp.x() * Scale - mouse_pos.x(), 2) + pow(cur_clamp.y() * Scale - mouse_pos.y(), 2) );
    };
    QMapIterator<int, function<QPointF (double, double)> > it(clamp);
    while (it.hasNext())
    {
        it.next();
        cur_clamp = it.value()(x, y);
        dis = determine_dis();
        if (dis < min_dis)
        {
            min_dis = dis;
            best_clamp = it.key();
        }
    }
    return min_dis < Scale * 3 ? pair<int, double>(best_clamp, min_dis) : pair<int, double>(-1, -1.0);
}

void FigureInterface::SetMainColor(QColor new_color)
{
    main_color = new_color;
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
    data["TEXT"][2] = *(new QVariant(Name));
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
    return pair<double, double>(cos(angel) * (point.first - x) - sin(angel) * (point.second - y) + x,
                                sin(angel) * (point.first - x) + cos(angel) * (point.second - y) + y);
}

QPointF FigureInterface::RotatePoint(QPointF point, double angel)
{
    angel *= M_PI / 180;
    return QPointF(cos(angel) * (point.x() - x) - sin(angel) * (point.y() - y) + x,
                   sin(angel) * (point.x() - x) + cos(angel) * (point.y() - y) + y);
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
        clamp = this->GetClampp(it.value());
        it.key()->update(this, clamp.first, clamp.second);
    }
}
