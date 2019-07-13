#include "objectmode.h"

ObjectMode::ObjectMode(QWidget *parent) : ModeInterface (parent) {}

void ObjectMode::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void ObjectMode::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
}
void ObjectMode::paintGL()
{
    QColor background(200, 200, 200, 255);
    qglClearColor(background);
//    qglClearColor(Qt::gray);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    // enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5);
    glColor3b(50, 50, 50);
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            glVertex2f(j * 75.0, i * 75.0);
        }
    }
    glEnd();
}

void ObjectMode::mousePressEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Down";
}

void ObjectMode::mouseMoveEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Move";
}

void ObjectMode::mouseReleaseEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Release";
}
