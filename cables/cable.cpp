#include "cable.h"
#include <QDebug>

Cable::Cable(int x, int y)
{
    points.push_back(pair<double, double>(x, y));
    main_color.setRgb(0, 0, 0);

    QVector<QVariant> item;
    item.push_back(*(new QVariant(QPointF(x, y))));
    data.insert("GL_LINES", item);
}

void Cable::update(IObservable *parent, double X, double Y)
{
    SetPoint(GetVertex(parent), X, Y);
}

void Cable::insert_back(double x, double y)
{
    points.push_back(pair<double, double>(x, y));
    data["GL_LINES"].push_back(*(new QVariant(QPointF(x, y))));
}

void Cable::RemoveLoops(QPoint pos, double scale)
{
    double distance;
    for(int i = 1; i < points.size(); i++)
    {
        distance = sqrt(pow(points[i].first * scale - pos.x(), 2) + pow(points[i].second * scale - pos.y(), 2));
        if (distance < scale)
        {
            points.erase(points.begin() + i + 1, points.end());
            BuilData();
            return;
        }
    }
}

bool Cable::CheckIntersection(pair<QPoint, QPoint> section, double scale)
{
    pair<double, double> a, b;
    double p, l, r;
    for (int i = 0; i < points.size() - 1; i++)
    {
        a = points[i];
        b = points[i + 1];
        if (CheckState(a, b))
        {
            p = (a.second * scale - section.first.y()) * (section.second.x() - section.first.x()) / (section.second.y() - section.first.y()) + section.first.x();
            l = section.first.x();
            r = section.second.x();
            if (section.first.x() > section.second.x())
                qSwap(l, r);
            if (p > l && p < r)
                return  true;
        }
        else
        {
            p = (a.first * scale - section.first.x()) * (section.second.y() - section.first.y()) / (section.second.x() - section.first.x()) + section.first.y();
            l = section.first.y();
            r = section.second.y();
            if (section.first.y() > section.second.y())
                qSwap(l, r);
            if (p > l && p < r)
                return  true;
        }
    }
    return false;
}

bool Cable::CheckIntersection(QPoint brush, double scale)
{
    pair<double, double> a, b;
    double l, r;
    for (int i = 0; i < points.size() - 1; i++)
    {
        a = points[i];
        b = points[i + 1];
        if (CheckState(a, b))
        {
            l = a.first * scale;
            r = b.first * scale;
            if (l > r)
                qSwap(l, r);
            if (brush.x() >= l && brush.x() <= r && abs(brush.y() - a.second * scale) <= scale * 2)
            {
//                qDebug() << "h" << l << r << brush;
                return true;
            }
        }
        else
        {
            l = a.second * scale;
            r = b.second * scale;
            if (l > r)
                qSwap(l, r);
            if (brush.y() >= l && brush.y() <= r && abs(brush.x() - a.first * scale) <= scale * 2)
            {
//                qDebug() << "v" << l << r << brush;
                return true;
            }
        }
    }
    return false;
}

bool Cable::CheckState(pair<double, double> a, pair<double, double> b)
{
    if (qFuzzyCompare(a.second, b.second))
        return true;
    return false;
}

bool Cable::CheckState(int i, int j)
{
    if (qFuzzyCompare(points[i].second, points[j].second))
        return  true;
    return false;
}

bool Cable::IsMarked()
{
    if (main_color != QColor(0, 0, 0))
        return true;
    return false;
}

void Cable::BuilData()
{
    data.clear();
    QVector<QVariant> item;
    for (int i = 0; i < points.size() - 1; i++)
    {
        item.push_back(*(new QVariant(QPointF(points[i].first, points[i].second))));
        item.push_back(*(new QVariant(QPointF(points[i + 1].first, points[i + 1].second))));
    }
    data.insert("GL_LINES", item);
}

void Cable::SetPoint(int i, double X, double Y)
{
    if (i == 0)
    {
        if (qFuzzyCompare(points[i].second, points[i + 1].second))
        {
            points[i] = pair<double, double>(X, Y);
            points[i + 1].second = points[i].second;
        }
        else
        {
            points[i] = pair<double, double>(X, Y);
            points[i + 1].first = points[i].first;
        }
    }
    else if (i == points.size() - 1)
    {
        if (qFuzzyCompare(points[i].second, points[i - 1].second))
        {
            points[i] = pair<double, double>(X, Y);
            points[i - 1].second = points[i].second;
        }
        else
        {
            points[i] = pair<double, double>(X, Y);
            points[i - 1].first = points[i].first;
        }
    }
    BuilData();
}

void Cable::SetPoint(int i, QPoint p)
{
    if (i == 0)
    {
        if (qFuzzyCompare(points[i].second, points[i + 1].second))
        {
            points[i] = pair<double, double>(p.x(), p.y());
            points[i + 1].second = points[i].second;
        }
        else
        {
            points[i] = pair<double, double>(p.x(), p.y());
            points[i + 1].first = points[i].first;
        }
    }
    else if (i == points.size() - 1)
    {
        if (qFuzzyCompare(points[i].second, points[i - 1].second))
        {
            points[i] = pair<double, double>(p.x(), p.y());
            points[i - 1].second = points[i].second;
        }
        else
        {
            points[i] = pair<double, double>(p.x(), p.y());
            points[i - 1].first = points[i].first;
        }
    }
    BuilData();
}

void Cable::SetMainColor(QColor color)
{
    main_color = color;
}
