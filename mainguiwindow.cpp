#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{

    ui->setupUi(this);
//    connect();
//    ui->pushButton;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(DCMode()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(OMode()));

}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::DCMode()
{
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}

void MainGUIWindow::OMode()
{
    qDebug() << "change mode";
    ui->widget->SetMode(new ObjectMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}
