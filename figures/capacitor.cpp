#include "capacitor.h"

capacitor::capacitor(int X, int Y) : FigureInterface(X, Y), c(1)
{
    clamp_coordiantes[1] = Clamp1;
    clamp_coordiantes[2] = Clamp2;
}

void capacitor::print(double Scale)
{
    glLineWidth(float(Scale / 5));
    glColor3d(main_color[0], main_color[1], main_color[2]);
    glBegin(GL_LINES);
    glVertex2d((x - 4) * Scale, y * Scale);
    glVertex2d((x - 0.5) * Scale, y * Scale);
    glVertex2d((x + 4) * Scale, y * Scale);
    glVertex2d((x + 0.5) * Scale, y * Scale);
    glVertex2d((x - 0.5) * Scale, (y + 1.5) * Scale);
    glVertex2d((x - 0.5) * Scale, (y - 1.5) * Scale);
    glVertex2d((x + 0.5) * Scale, (y + 1.5) * Scale);
    glVertex2d((x + 0.5) * Scale, (y - 1.5) * Scale);
    glEnd();
}

QPoint capacitor::SelectClamp(QPoint)
{
    return QPoint(0, 0);
}
