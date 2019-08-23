#ifndef MAINGUIWINDOW_H
#define MAINGUIWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QSplitter>
#include <QLabel>
#include <QListWidget>
#include <QComboBox>

#include "view/qtree.h"
#include "view/style/qstylesheetstring.h"

namespace Ui {
class MainGUIWindow;
}

class MainGUIWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *modes;
    QWidget *actions;
    QWidget *allFigures;
    QWidget *propereties;
    QWidget *listNew;

    QLineEdit *name;
    QLineEdit *value;
public:
    explicit MainGUIWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    ~MainGUIWindow();
private:
    Ui::MainGUIWindow *ui;
    void ClearLayout(QLayout *);
private slots:
    void SetDrawCableMode();
    void SetObjectMode();
    void LoadPropereties(QString, QString);
    void ClearPropereties();
};

#endif // MAINGUIWINDOW_H
