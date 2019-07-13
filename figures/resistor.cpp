#include "resistor.h"

void Resistor::print()
{
    glColor3b(250.0, 50.0, 50.0);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2i(x - 150, y);
    glVertex2i(x - 225, y);
    glVertex2i(x + 150, y);
    glVertex2i(x + 225, y);
    glEnd();
}
