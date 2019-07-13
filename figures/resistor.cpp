#include "resistor.h"

void Resistor::print()
{
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + 50, y + 100);
    glEnd();
}
