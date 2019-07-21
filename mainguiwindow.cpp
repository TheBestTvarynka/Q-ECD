#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{

    ui->setupUi(this);
//    connect();
//    ui->pushButton;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ChangeMode()));
}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::ChangeMode()
{
    qDebug() << "change mode";
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));

}
