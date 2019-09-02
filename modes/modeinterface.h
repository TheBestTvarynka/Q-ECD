#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QVariant>

class PaintBoard;

class ModeInterface
{
public:
    QMap<QString, QVector<QVariant> > data;
    QColor color;
    PaintBoard *Parent;
    double scale;

    explicit ModeInterface(PaintBoard *, double);
    virtual void mousePressEvent(QMouseEvent *) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *);
    QMap<QString, QVector<QVariant> > GetData() { return data; }
    QColor GetDataColor() { return color; }
    QPoint RoundCoordinates(double, double);
    virtual ~ModeInterface();
};

#endif // MODEINTERFACE_H
