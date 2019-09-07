#include "figurecreator.h"

FigureCreator::FigureCreator()
{
    DATA.insert("Capacitor", &FigureCreator::CapacitorData);
    DATA.insert("Resistor", &FigureCreator::ResistorData);
    CLAMP.insert("Capacitor", &FigureCreator::CapacitorClamp);
    CLAMP.insert("Resistor", &FigureCreator::ResistorClamp);
}

QMap<QString, QVector<QVariant> > FigureCreator::ResistorData(double x, double y, QString name)
{
    QMap<QString, QVector<QVariant> > data;
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
    return data;
}

QMap<int, function<QPointF (double, double)> > FigureCreator::ResistorClamp()
{
    QMap<int, function<QPointF (double, double)> > clamp;
    clamp.insert(0, [] (double x, double y) { return QPointF(x + 4, y); });
    clamp.insert(1, [] (double x, double y) { return QPointF(x - 4, y); });
    return clamp;
}

QMap<QString, QVector<QVariant> > FigureCreator::CapacitorData(double x, double y, QString name)
{
        QMap<QString, QVector<QVariant> > data;
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
        return data;
}

QMap<int, function<QPointF (double, double)> > FigureCreator::CapacitorClamp()
{
    QMap<int, function<QPointF (double, double)> > clamp;
    clamp.insert(0, [] (double x, double y) { return QPointF(x + 4, y); });
    clamp.insert(1, [] (double x, double y) { return QPointF(x - 4, y); });
    return clamp;
}
