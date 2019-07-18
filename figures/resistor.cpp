#include "resistor.h"

void Resistor::print(double Scale)
{
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINE_LOOP);
    glColor3d(10, 10, 10);
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
}
