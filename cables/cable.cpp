#include "cable.h"

Cable::Cable(int x, int y)
{
    points.push_back(pair<double, double>(x, y));
}

void Cable::print(double Scale)
{
    glLineWidth(float(Scale / 5));
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for(int i = 0; i < points.size() - 1; i++)
    {
        glVertex2d(points[i].first * Scale, points[i].second * Scale);
        glVertex2d(points[i + 1].first * Scale, points[i + 1].second * Scale);
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

void Cable::RemoveLoops(QPoint pos, double scale)
{
    double distance;
    for(int i = 1; i < points.size(); i++)
    {
        distance = sqrt(pow(points[i].first * scale - pos.x(), 2) + pow(points[i].second * scale - pos.y(), 2));
        if (distance < scale)
        {
            points.erase(points.begin() + i + 1, points.end());

            return;
        }
    }
}
