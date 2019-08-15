#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "data/datafigures.h"
#include "data/datacables.h"
#include "modes/modeinterface.h"
#include "modes/objectmode.h"
#include "modes/drawcablemode.h"

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>
#include "figures/figurecreator.h"

using std::pair;

class PaintBoard : public QGLWidget
{
    Q_OBJECT
    QTimer mpTimer;
    ModeInterface *mode;
    DataFigures figures;
    DataCables cables;
    FigureCreator creator;

    QPoint Delta;
    double Scale;
    // temp variavle. use when we drag a mouse
    QPoint start_position;
    Qt::MouseButton click;
public:
    PaintBoard(QWidget *parent = 0, ModeInterface *start_state = nullptr);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void RenderText(pair<double, double>, double, QString);

    double GetScale() { return Scale; }
    QPoint GetCenter() { return mode->GetCenter(); }

    DataFigures *GetDataFigures() { return &figures; }
    DataCables *GetDataCables() { return &cables; }
    void SetMode(ModeInterface *);
public slots:
    void SetSelectedFigure(FigureInterface *);
    void CreateFigure(int);
    void RemoveSelectedFigure();
    void SetNameSelectedFigure(const QString &);
    void SetValueSelectedFigure(const QString &);
    void RotateSelectedFigureRight();
    void RotateSelectedFigureLeft();
signals:
    void AddToTree(FigureInterface *);
    void LoadFigurePropereties(QString, QString);
    void ClearPropereties();
};

#endif // PAINTBOARD_H
