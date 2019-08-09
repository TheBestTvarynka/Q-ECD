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
public:
    explicit MainGUIWindow(QWidget *parent = nullptr);
    ~MainGUIWindow();

private:
    Ui::MainGUIWindow *ui;
    void ClearLayout(QLayout *);
private slots:
    void SetDrawCableMode();
    void SetObjectMode();
};

#endif // MAINGUIWINDOW_H
