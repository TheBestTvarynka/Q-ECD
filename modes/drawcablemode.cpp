#include "drawcablemode.h"

DrawCableMode::DrawCableMode(PaintBoard *p, double s, QPoint c, QWidget *parent) : ModeInterface (s, p, parent) { Center = c;}

void DrawCableMode::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DrawCableMode::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);

    Weight = w;
    Height = h;
}

void DrawCableMode::paintGL(QPoint &Delta)
{
    QColor background(220, 220, 220, 255);
//    qglClearColor(background);
    glClearColor(220, 220, 220, 255);
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

    glColor3d(1.0, 1.0, 0.0);

    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(scale / 10));
    glBegin(GL_POINTS);

    int nV = int(Weight / scale) + 1;
    int nH = int(Height / scale) + 1;
    qDebug() << nV << " " << nH;
    double DeltaX = Center.x() - int(Center.x() / scale) * scale, DeltaY = Center.y() - int(Center.y() / scale) * scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * scale - Center.x() + DeltaX), float(i * scale - Center.y() + DeltaY));
        }
    }
    glEnd();
}

void DrawCableMode::mousePressEvent(QMouseEvent *)
{

}

void DrawCableMode::mouseMoveEvent(QMouseEvent *)
{
    qDebug() << "Mouse Move: ";
}

void DrawCableMode::mouseReleaseEvent(QMouseEvent *)
{

}
