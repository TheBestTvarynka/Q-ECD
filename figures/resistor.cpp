#include "resistor.h"
#include "paintboard.h"

Resistor::Resistor(int X, int Y, QString N) : FigureInterface(X, Y, N), r(1)
{
    clamp_coordiantes[0] = Clamp1;
    clamp_coordiantes[1] = Clamp2;
    nameX = 0;
    nameY = -1.2;
}

void Resistor::print(double Scale, PaintBoard *Parent)
{
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINE_LOOP);
    glColor3d(main_color[0], main_color[1], main_color[2]);
    glVertex2d((x - 2) * Scale, (y + 1) * Scale);
    glVertex2d((x + 2) * Scale, (y + 1) * Scale);
    glVertex2d((x + 2) * Scale, (y - 1) * Scale);
    glVertex2d((x - 2) * Scale, (y - 1) * Scale);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d((x - 2) * Scale, y * Scale);
    glVertex2d((x - 4) * Scale, y * Scale);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d((x + 2) * Scale, y * Scale);
    glVertex2d((x + 4) * Scale, y * Scale);
    glEnd();
    Parent->RenderText(x + nameX, y + nameY, name);
}
