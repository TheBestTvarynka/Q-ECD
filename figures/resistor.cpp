#include "resistor.h"
#include "paintboard.h"

Resistor::Resistor(int X, int Y, int R, QString N, QString V, int T) : FigureInterface(X, Y, R, N, V, T), r(1)
{
    clamp_coordiantes[0] = Clamp1;
    clamp_coordiantes[1] = Clamp2;
    nameX = 0;
    nameY = -1.2;

    QVector<QVariant> item;
    item.push_back(*(new QVariant(QPointF(-2, 1))));
    item.push_back(*(new QVariant(QPointF(2, 1))));
    item.push_back(*(new QVariant(QPointF(2, -1))));
    item.push_back(*(new QVariant(QPointF(-2, -1))));
    data.insert("GL_LINE_LOOP", item);
    QVector<QVariant> lines;
    lines.push_back(*(new QVariant(QPointF(-2, 0))));
    lines.push_back(*(new QVariant(QPointF(-4, 0))));
    lines.push_back(*(new QVariant(QPointF(2, 0))));
    lines.push_back(*(new QVariant(QPointF(4, 0))));
    data.insert("GL_LINES", lines);
    QVector<QVariant> text;
    text.push_back(*(new QVariant(QPointF(x, y))));
    text.push_back(*(new QVariant(QPointF(0, -1.2))));
    text.push_back(*(new QVariant(name)));
    data.insert("TEXT", text);

    clamp.insert(0, [] (double x, double y) { return QPointF(x + 4, y); });
    clamp.insert(1, [] (double x, double y) { return QPointF(x - 4, y); });
}
