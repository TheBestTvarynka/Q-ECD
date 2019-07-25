#include "cable.h"

Cable::Cable(int x, int y)
{
    points.push_back(pair<double, double>(x, y));
}

void Cable::print(double Scale)
{
    glLineWidth(20);
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < points.size(); i++)
    {
        glVertex2d(points[i].first * Scale, points[i].second * Scale);
    }
    glEnd();
}

void Cable::update()
{

}

void Cable::insert_back(double x, double y)
{
    points.push_back(pair<double, double>(x, y));
}
