#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include "data/datafigures.h"
#include "data/datacables.h"
#include "modes/modeinterface.h"
#include "modes/objectmode.h"
#include "modes/drawcablemode.h"
#include "modes/removecablemode.h"
#include "figures/figurecreator.h"

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>
#include <QClipboard>
#include <QApplication>

using std::pair;

class PaintBoard : public QGLWidget
{
    Q_OBJECT
    QColor grid;
    QColor figure;
    QColor figure_seleced;
    QColor cable;
    QColor cable_selected;

    QTimer mpTimer;
    ModeInterface *mode;
    DataFigures figures;
    DataCables cables;
    FigureCreator creator;

    QPoint Delta;
    QPoint Center;
    double Scale;
    // temp variavle. use when we drag a mouse
    QPoint start_position;
    Qt::MouseButton click;

    typedef void (PaintBoard::*PaintDevice)(QVector<QVariant>, QColor);
    QMap<QString, PaintDevice> paint_devices;
public:
    PaintBoard(QWidget *parent = nullptr, ModeInterface *start_state = nullptr);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *event);
    // painter device
    void LINES(QVector<QVariant>, QColor);
    void LINE_LOOP(QVector<QVariant>, QColor);
    void TEXT(QVector<QVariant>, QColor);
    /////////////////
    double GetScale() { return Scale; }
    QPoint GetCenter() { return Center; }
    DataFigures *GetDataFigures() { return &figures; }
    DataCables *GetDataCables() { return &cables; }
    void SetMode(ModeInterface *);
    void CreateCustomFigure(int, int, int, int, QString, QString);
public slots:
    void CreateFigure(int);
    void CopySelectedFigure();
    void PasteFromBuffer();
    void SetRemoveCableMode();
signals:
    void AddToTree(FigureInterface *);
    void LoadFigurePropereties(QString, QString);
    void ClearPropereties();
};

#endif // PAINTBOARD_H
