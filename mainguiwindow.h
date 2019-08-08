#ifndef MAINGUIWINDOW_H
#define MAINGUIWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
    QWidget *actions;
    QWidget *allFigures;
    QWidget *propereties;
    QWidget *listNew;
public:
    explicit MainGUIWindow(QWidget *parent = nullptr);
    ~MainGUIWindow();

private:
    Ui::MainGUIWindow *ui;
private slots:
    void SetDrawCableMode();
    void SetObjectMode();
    void DCMode();
    void OMode();
};

#endif // MAINGUIWINDOW_H
