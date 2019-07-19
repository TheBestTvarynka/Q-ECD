#include "capacitor.h"

void capacitor::print(double Scale)
{
    glLineWidth(float(Scale / 5));
    glColor3d(0.0, 1.0, 0.0);
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
