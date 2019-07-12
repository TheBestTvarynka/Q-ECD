#ifndef MAINGUIWINDOW_H
#define MAINGUIWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainGUIWindow;
}

class MainGUIWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainGUIWindow(QWidget *parent = nullptr);
    ~MainGUIWindow();

private:
    Ui::MainGUIWindow *ui;
};

#endif // MAINGUIWINDOW_H
