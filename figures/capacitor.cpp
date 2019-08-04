#include "capacitor.h"
#include "paintboard.h"

capacitor::capacitor(int X, int Y, QString N) : FigureInterface(X, Y, N), c(1)
{
    clamp_coordiantes[0] = Clamp1;
    clamp_coordiantes[1] = Clamp2;
    nameX = 0;
    nameY = -1.6;
}

void capacitor::print(double Scale, PaintBoard *Parent)
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
    Parent->RenderText(x + nameX, y + nameY, name);
}
