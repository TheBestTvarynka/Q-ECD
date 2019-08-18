#include "removecablemode.h"
#include "paintboard.h"
#include <QFont>

RemoveCableMode::RemoveCableMode(PaintBoard *p, double s, QPoint c, int w, int h) : ModeInterface (s, p, w, h)
{
    Center = c;
    click = Qt::MouseButton::NoButton;
    line.first = QPoint(0, 0);
    line.second = line.first;
}

void RemoveCableMode::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RemoveCableMode::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);

    Weight = w;
    Height = h;
}

void RemoveCableMode::paintGL(QPoint &Delta)
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

    glColor3d(0.3, 0.5, 0.1);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();

    glPointSize(int(scale / 10));
    glBegin(GL_POINTS);

    int nV = int(Weight / scale) + 1;
    int nH = int(Height / scale) + 1;

    double DeltaX = Center.x() - int(Center.x() / scale) * scale, DeltaY = Center.y() - int(Center.y() / scale) * scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * scale - Center.x() + DeltaX), float(i * scale - Center.y() + DeltaY));
        }
    }
    glEnd();

    Parent->GetDataCables()->print(scale);
    Parent->GetDataFigures()->print(scale, Parent);

    glEnable(GL_LINE_STIPPLE);
    glColor3d(0.8, 0.1, 0.2);
//    glLineStipple(1, 0x00F0);
    glLineStipple(0, 0xAAAA);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(line.first.x(), line.first.y());
    glVertex2i(line.second.x(), line.second.y());
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void RemoveCableMode::mousePressEvent(QMouseEvent *ap)
{
    line.first = ap->pos();
    line.first -= Center;
    line.second = line.first;
}

void RemoveCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    line.second = ap->pos() - Center;
}

void RemoveCableMode::mouseReleaseEvent(QMouseEvent *)
{
//    line.first = line.second = QPoint(0, 0);
    line.first = line.second;
}

