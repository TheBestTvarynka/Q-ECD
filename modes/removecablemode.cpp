#include "removecablemode.h"
#include "paintboard.h"
#include <QFont>

RemoveCableMode::RemoveCableMode(PaintBoard *p, double s, QPoint c, int w, int h) : ModeInterface (s, p, w, h)
{
    Center = c;
    click = Qt::MouseButton::NoButton;
    line.first = QPoint(0, 0);
    line.second = line.first;
    selected_cables.clear();
    brush = QPoint(0, 0);
    radius = 0;
}

void RemoveCableMode::paintGL(QPoint &Delta)
{
    QColor background(220, 220, 220, 255);
    glClearColor(220, 220, 220, 255);
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

    double theta, x, y;
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 30; i++)
    {
        theta = 2.0 * 3.1415926 * double(i) / double(30);
        x = radius * cos(theta);
        y = radius * sin(theta);
        glVertex2d(x + brush.x(), y + brush.y());
    }
    glEnd();
}

void RemoveCableMode::mousePressEvent(QMouseEvent *ap)
{
    Parent->setCursor(Qt::BlankCursor);
//    Parent->setCursor(Qt::CrossCursor);
    brush = ap->pos();
    radius = 2 * scale;
}

void RemoveCableMode::mouseMoveEvent(QMouseEvent *ap)
{
    brush = ap->pos() - Center;
    QList<Cable *> new_selected = Parent->GetDataCables()->GetForDeleting(brush, scale);
    if (!shiftPressed)
    {
        Parent->GetDataCables()->SetCablesColor(new_selected, new double[3]{0.8, 0.9, 0.9});
//        selected_cables += new_selected;
        Parent->GetDataCables()->AddToSelected(new_selected);
    }
    else
    {
        qDebug() << "remove" << new_selected.size();
        Parent->GetDataCables()->SetCablesColor(new_selected, new double[3]{0.0, 0.0, 0.0});
        Parent->GetDataCables()->RemoveFromSelected(new_selected);
    }
}

void RemoveCableMode::mouseReleaseEvent(QMouseEvent *)
{
//    Parent->GetDataCables()->SetSelected(selected_cables);
    Parent->setCursor(Qt::ArrowCursor);
    radius = 0;
}

void RemoveCableMode::keyPressEvent(QKeyEvent *event)
{
//    shiftPressed = true;
    if (event->key() == 16777248)
    {
        qDebug() << "event->key()";
        shiftPressed = true;
    }
}

void RemoveCableMode::keyReleaseEvent(QKeyEvent *)
{
    shiftPressed = false;
}
