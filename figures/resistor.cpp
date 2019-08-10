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

    Parent->RenderText(x + nameX, y + nameY, name);
}
