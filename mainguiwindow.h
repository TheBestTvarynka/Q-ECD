#ifndef MAINGUIWINDOW_H
#define MAINGUIWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
private slots:
    void DCMode();
    void OMode();
};

#endif // MAINGUIWINDOW_H
