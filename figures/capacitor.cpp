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
}

void Capacitor::print(double Scale, PaintBoard *Parent)
{
    glLineWidth(float(Scale / 5));
    glColor3d(main_color[0], main_color[1], main_color[2]);

    glPushMatrix();
    glTranslated(x * Scale, y * Scale, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    glVertex2d((-4) * Scale, 0);
    glVertex2d((-0.5) * Scale, 0);
    glVertex2d((4) * Scale, 0);
    glVertex2d((0.5) * Scale, 0);
    glVertex2d((-0.5) * Scale, (1.5) * Scale);
    glVertex2d((-0.5) * Scale, (-1.5) * Scale);
    glVertex2d((0.5) * Scale, (1.5) * Scale);
    glVertex2d((0.5) * Scale, (-1.5) * Scale);
    glEnd();

    glPopMatrix();

//    Parent->RenderText(x + nameX, y + nameY, name);
//    Parent->RenderText(RotatePoint(pair<double, double>(x + nameX, y + nameY), rotation), rotation, name);
}
