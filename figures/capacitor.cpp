#include "capacitor.h"
#include "paintboard.h"

Capacitor::Capacitor(int X, int Y, int R, QString N, QString V, int T) : FigureInterface(X, Y, R, N, V, T), c(1)
{
    clamp_coordiantes[0] = Clamp1;
    clamp_coordiantes[1] = Clamp2;
    nameX = 0;
    nameY = -1.6;

    QVector<QVariant> item;
    item.push_back(*(new QVariant(QPointF(-4, 0))));
    item.push_back(*(new QVariant(QPointF(-0.5, 0))));
    item.push_back(*(new QVariant(QPointF(4, 0))));
    item.push_back(*(new QVariant(QPointF(0.5, 0))));
    item.push_back(*(new QVariant(QPointF(-0.5, 1.5))));
    item.push_back(*(new QVariant(QPointF(-0.5, -1.5))));
    item.push_back(*(new QVariant(QPointF(0.5, 1.5))));
    item.push_back(*(new QVariant(QPointF(0.5, -1.5))));
    data.insert("GL_LINES", item);
    QVector<QVariant> text;
    text.push_back(*(new QVariant(QPointF(x, y))));
    text.push_back(*(new QVariant(QPointF(0, -1.6))));
    text.push_back(*(new QVariant(name)));
    data.insert("TEXT", text);

    clamp.insert(0, [] (double x, double y) { return QPointF(x + 4, y); });
    clamp.insert(1, [] (double x, double y) { return QPointF(x - 4, y); });
}
