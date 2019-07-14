#include "objectmode.h"

ObjectMode::ObjectMode(QWidget *parent) : ModeInterface (parent) { Center = QPoint(0, 0);}

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
    Weight = w;
    Height = h;
}
void ObjectMode::paintGL(double Scale, QPoint &Delta)
{
    QColor background(220, 220, 220, 255);
    qglClearColor(background);
//    qglClearColor(Qt::gray);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    // enable alfa
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTranslated(Delta.x(), Delta.y(), 0);
    Center += Delta;
    Delta = QPoint(0, 0);

    glPointSize(int(Scale / 10));
    glColor3i(150, 150, 150);
    glBegin(GL_POINTS);

    int nV = int(Weight / Scale) + 1;
    int nH = int(Height / Scale) + 1;
    int DeltaX = Center.x() % int(Scale), DeltaY = Center.y() % int(Scale);
//    qDebug() << DeltaX << " " << DeltaY;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * Scale - Center.x() + DeltaX), float(i * Scale - Center.y() + DeltaY));
        }
    }
    glEnd();
}

void ObjectMode::mousePressEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Down " << ap->x();
}

void ObjectMode::mouseMoveEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Move" << ap->x();
}

void ObjectMode::mouseReleaseEvent(QMouseEvent *ap)
{
    qDebug() << "Mouse Release" << ap->x();
}
