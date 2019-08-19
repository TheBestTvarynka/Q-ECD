#ifndef REMOVECABLEMODE_H
#define REMOVECABLEMODE_H

#include "modeinterface.h"
#include "cables/cable.h"

#include <QDebug>

using std::pair;

class RemoveCableMode : public ModeInterface
{
    QPoint start_position;
    Qt::MouseButton click;

    pair<QPoint, QPoint> line;
    QPoint brush;
    double radius;
    QList<Cable *> selected_cables;
    bool shiftPressed;
public:
    explicit RemoveCableMode(PaintBoard *, double, QPoint, int, int);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL(QPoint &);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // REMOVECABLEMODE_H
