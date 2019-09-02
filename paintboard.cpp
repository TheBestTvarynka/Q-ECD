#include "paintboard.h"
#include <QDebug>

PaintBoard::PaintBoard(QWidget *parent, ModeInterface *start_state): QGLWidget(parent)
{
    Scale = 20;
    Delta.setX(0);
    Delta.setY(0);
    Center = Delta;
    click = Qt::MouseButton::NoButton;

    paint_devices.insert("GL_LINE_LOOP", &PaintBoard::LINE_LOOP);
    paint_devices.insert("GL_LINES", &PaintBoard::LINES);
    paint_devices.insert("TEXT", &PaintBoard::TEXT);
    paint_devices.insert("CIRCLE", &PaintBoard::CIRCLE);
    paint_devices.insert("CIRCLE_FULL", &PaintBoard::CIRCLE_FULL);

    connect(&mpTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mpTimer.start(10);

    if (start_state == nullptr)
        mode = new ObjectMode(this, Scale);
}

void PaintBoard::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 649, 649, 0, 0, 1);
    glEnable (GL_TEXTURE_2D);
    ////////// enable alfa
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PaintBoard::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glViewport(0, 0, w, h);
    glTranslated(Center.x(), Center.y(), 0);
}

void PaintBoard::paintGL()
{
    QColor background(220, 220, 220, 255);
    glClearColor(220, 220, 220, 255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw central point
    glColor3d(0.0, 0.0, 1.0);
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(float(0), float(0));
    glEnd();
    // draw grid
    glPointSize(int(Scale / 10));
    glBegin(GL_POINTS);
    int nV = int(width() / Scale) + 1;
    int nH = int(height() / Scale) + 1;
    double DeltaX = Center.x() - int(Center.x() / Scale) * Scale, DeltaY = Center.y() - int(Center.y() / Scale) * Scale;
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            glVertex2f(float(j * Scale - Center.x() + DeltaX), float(i * Scale - Center.y() + DeltaY));
        }
    }
    glEnd();
    // draw figures
    QVector<FigureInterface *> f = figures.GetFigures();
    QMap<QString, QVector<QVariant> > d;
    pair<double, double> pos;
    foreach (FigureInterface *i, f)
    {
        d = i->GetData();
        pos = i->GetPos();
        glPushMatrix();
        glTranslated(pos.first * Scale, pos.second * Scale, 0);
        glRotatef(i->GetRotation(), 0.0, 0.0, 1.0);

        QMapIterator<QString, QVector<QVariant> > iT(d);
        while (iT.hasNext())
        {
            iT.next();
            (this->*paint_devices[iT.key()])(iT.value(), QColor(i->GetColor()));
        }

        glPopMatrix();
    }
    // draw cables
    QVector<Cable *> c = cables.GetCables();
    foreach (Cable *i, c)
    {
        d = i->GetData();
        QMapIterator<QString, QVector<QVariant> > iT(d);
        while (iT.hasNext())
        {
            iT.next();
            (this->*paint_devices[iT.key()])(iT.value(), i->GetColor());
        }
    }
    // draw data from mode
    d = mode->GetData();
    QMapIterator<QString, QVector<QVariant> > iT(d);
    while (iT.hasNext())
    {
        iT.next();
        (this->*paint_devices[iT.key()])(iT.value(), mode->GetDataColor());
    }
}

void PaintBoard::mousePressEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        start_position = ap->pos();
        click = Qt::MouseButton::MidButton;
    }
    else
    {
        mode->mousePressEvent(ap);
    }
}

void PaintBoard::mouseMoveEvent(QMouseEvent *ap)
{
    if (ap->buttons() == Qt::MidButton)
    {
        Delta = ap->pos() - start_position;
        Center += Delta;
        glTranslated(Delta.x(), Delta.y(), 0);
        start_position = ap->pos();
    }
    else
    {
        mode->mouseMoveEvent(ap);
    }
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *ap)
{
    if (click == Qt::MidButton)
    {
        click = Qt::MouseButton::NoButton;
    }
    else
    {
        mode->mouseReleaseEvent(ap);
    }
}

void PaintBoard::wheelEvent(QWheelEvent *event)
{
    QPoint new_Center;
    QPoint mouse = event->pos();
    double new_Scale = 10.0;

    int n = int((mouse.x() - Center.x()) / Scale);
    double k = mouse.x() - Center.x() - n * Scale;
    if (event->angleDelta().y() > 0)
    {
        k *= 1.1;
        new_Scale = Scale * 1.1;
    }
    else
    {
        k *= 0.9;
        new_Scale = Scale * 0.9;
    }
    new_Center.setX( int(mouse.x() - new_Scale * n - k) );

    n = int((mouse.y() - Center.y()) / Scale);
    k = mouse.y() - Center.y() - n * Scale;
    if (event->angleDelta().y() > 0)
    {
        k *= 1.1;
    }
    else
    {
        k *= 0.9;
    }
    new_Center.setY( int(mouse.y() - new_Scale * n - k) );

    Scale = new_Scale;
    Center = new_Center;
    resizeGL(width(), height());
}

void PaintBoard::keyPressEvent(QKeyEvent *event)
{
    mode->keyPressEvent(event);
}

void PaintBoard::keyReleaseEvent(QKeyEvent *event)
{
    mode->keyReleaseEvent(event);
}

void PaintBoard::LINES(QVector<QVariant> lines, QColor color)
{
    QPointF point;
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINES);
    glColor3ub(GLubyte(color.red()), GLubyte(color.green()), GLubyte(color.blue()));
    foreach (QVariant i, lines)
    {
        point = i.toPointF();
        glVertex2f(float(point.x()) * float(Scale), float(point.y()) * float(Scale));
    }
    glEnd();
}

void PaintBoard::LINE_LOOP(QVector<QVariant> lines, QColor color)
{
    QPointF point;
    glLineWidth(float(Scale / 5));
    glBegin(GL_LINE_LOOP);
    glColor3ub(GLubyte(color.red()), GLubyte(color.green()), GLubyte(color.blue()));
    foreach (QVariant i, lines)
    {
        point = i.toPointF();
        glVertex2f(float(point.x()) * float(Scale), float(point.y()) * float(Scale));
    }
    glEnd();
}

void PaintBoard::TEXT(QVector<QVariant> text, QColor color)
{
    if (text.size() != 3)
        return;
    QPointF f_pos = text[0].toPointF();
    QPointF pos = text[1].toPointF();
    glColor3ub(GLubyte(color.red()), GLubyte(color.green()), GLubyte(color.blue()));
    renderText(Center.x() + int(pos.x() * Scale + f_pos.x() * Scale), Center.y() + int(pos.y() * Scale + f_pos.y() * Scale), text[2].toString(), QFont("Arial", int(Scale * 0.67), 5, false));
}

void PaintBoard::CIRCLE(QVector<QVariant> circle, QColor color)
{
    if (circle.size() != 2)
        return;
    double theta, x, y;
    QPointF brush = circle[0].toPointF();
    double radius = circle[1].toDouble();
    glColor3ub(GLubyte(color.red()), GLubyte(color.green()), GLubyte(color.blue()));
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 30; i++)
    {
        theta = 2.0 * 3.1415926 * double(i) / double(30);
        x = radius * cos(theta);
        y = radius * sin(theta);
        glVertex2d(x + brush.x() * Scale, y + brush.y() * Scale);
    }
    glEnd();
}

void PaintBoard::CIRCLE_FULL(QVector<QVariant> circle, QColor color)
{
    if (circle.size() != 2)
        return;
    double theta, x, y;
    QPointF brush = circle[0].toPointF();
    double radius = circle[1].toDouble();
    glColor3ub(GLubyte(color.red()), GLubyte(color.green()), GLubyte(color.blue()));
    glLineWidth(3);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++)
    {
        theta = 2.0 * 3.1415926 * double(i) / double(30);
        x = radius * cos(theta);
        y = radius * sin(theta);
        glVertex2d(x + brush.x() * Scale, y + brush.y() * Scale);
    }
    glEnd();
}

void PaintBoard::SetMode(ModeInterface *newMode)
{
    delete mode;
    mode = newMode;
}

void PaintBoard::CreateCustomFigure(int type, int x, int y, int rotation, QString name, QString value)
{
    FigureInterface *new_figure = creator.GetNewFigure(type, x, y, rotation, name, value);
    figures.add(new_figure);
    emit AddToTree(new_figure);
}

void PaintBoard::CreateFigure(int f)
{
    FigureInterface *new_figure = creator.GetNewFigure(f, int((width() / 2 - Center.x()) / Scale), int((height() / 2 - Center.y()) / Scale), 0, "F" + QString::number(figures.size()), "vl");
    figures.add(new_figure);
    emit AddToTree(new_figure);
}

void PaintBoard::CopySelectedFigure()
{
    FigureInterface *selected = figures.GetSelectedFigure();
    if (selected == nullptr)
        return;
    QString x; x.setNum(selected->GetX());
    QString y; y.setNum(selected->GetY());
    QString r; r.setNum(selected->GetRotation());
    QString n = selected->GetName();
    QString v = selected->GetValue();
    QString t; t.setNum(selected->GetType());
    QString buffer = x + ";" + y + ";" + r + ";" + n + ";" + v + ";" + t;
    qDebug() << buffer;
    QClipboard *buf = QApplication::clipboard();
    buf->setText(buffer);
}

void PaintBoard::PasteFromBuffer()
{
    QClipboard *buffer = QApplication::clipboard();
    QString str = buffer->text();
    if (str.isNull())
        return;
    int x =  str.section(';', 0, 0).toInt();
    int y = str.section(';', 1, 1).toInt();
    int rotation = str.section(';', 2, 2).toInt();
    QString name = str.section(';', 3, 3);
    QString value = str.section(';', 4, 4);
    int type =  str.section(';', 5, 5).toInt();
    CreateCustomFigure(type, x, y, rotation, name, value);
}

void PaintBoard::SetRemoveCableMode()
{
    ModeInterface *Mode = new RemoveCableMode(this, GetScale());
    delete mode;
    mode = Mode;
}
