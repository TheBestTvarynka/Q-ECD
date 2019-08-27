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
    item.push_back(*(new QVariant(QPointF(-1, -1))));
    data.insert("GL_LINE_LOOP", item);
    QVector<QVariant> lines;
    lines.push_back(*(new QVariant(QPointF(-2, 0))));
    lines.push_back(*(new QVariant(QPointF(-4, 0))));
    lines.push_back(*(new QVariant(QPointF(2, 0))));
    lines.push_back(*(new QVariant(QPointF(4, 0))));
    data.insert("GL_LINES", lines);
    QVector<QVariant> text;
    text.push_back(*(new QVariant(QPointF(0, -1.2))));
    text.push_back(*(new QVariant(name)));
    data.insert("TEXT", text);
}

void Resistor::print(double Scale, PaintBoard *Parent)
{
    glLineWidth(float(Scale / 5));
    glColor3d(main_color[0], main_color[1], main_color[2]);

    glPushMatrix();
    glTranslated(x * Scale, y * Scale, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    glVertex2d((-2) * Scale, Scale);
    glVertex2d((2) * Scale, Scale);
    glVertex2d((2) * Scale, (-1) * Scale);
    glVertex2d((-2) * Scale, (-1) * Scale);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d((-2) * Scale, 0);
    glVertex2d((-4) * Scale, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d((2) * Scale, 0);
    glVertex2d((4) * Scale, 0);
    glEnd();

    glPopMatrix();

    Parent->RenderText(RotatePoint(pair<double, double>(x + nameX, y + nameY), rotation), rotation, name);
}
