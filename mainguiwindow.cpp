#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QSplitter>
#include <QLabel>
#include <QListWidget>
#include <QComboBox>

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{

    ui->setupUi(this);
//    connect();
//    ui->pushButton;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(DCMode()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(OMode()));

    QLineEdit *info = new QLineEdit("bleh bleh bleh");
    QLineEdit *name = new QLineEdit("name bleh bleh");
    QLineEdit *var = new QLineEdit("var bleh bleh");
    QSpacerItem *space_up = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    QVBoxLayout *propereties = new QVBoxLayout;
    propereties->addWidget(info);
    propereties->addWidget(name);
    propereties->addWidget(var);
    propereties->addItem(space_up);

    QWidget *right_down = new QWidget(this);
    right_down->setLayout(propereties);

    QLabel *res = new QLabel("resistor");
    QLabel *cap = new QLabel("capasitor");
    QSpacerItem *space_up2 = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    QVBoxLayout *list = new QVBoxLayout;
    list->addWidget(res);
    list->addWidget(cap);
    list->addItem(space_up2);

    QWidget *right_up = new QWidget;
    right_up->setLayout(list);

    QSplitter *right_bar = new QSplitter(Qt::Vertical);
    right_bar->addWidget(right_up);
    right_bar->addWidget(right_down);

    QListWidget *list_new = new QListWidget;
    list_new->addItem("resistor");
    list_new->addItem("qkation");
    list_new->addItem("dimka");
    QVBoxLayout *obj_mode = new QVBoxLayout;
    obj_mode->addWidget(list_new);

    QWidget *left_bar = new QWidget;
    left_bar->setLayout(obj_mode);

    QSplitter *main_area = new QSplitter(Qt::Horizontal);
//    main_area->addWidget(right_up);
//    main_area->addWidget(right_down);
    main_area->addWidget(left_bar);
    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    main_area->addWidget(ui->widget);
    main_area->addWidget(right_bar);

    QLabel *logo = new QLabel("Q-ECD");
    QComboBox *mode = new QComboBox;
    mode->addItem("object");
    mode->addItem("draw cable");

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QHBoxLayout *menu = new QHBoxLayout;
    menu->addWidget(ui->pushButton);
    menu->addWidget(ui->pushButton_2);
    menu->addItem(space);
    QWidget *actions = new QWidget;
    actions->setLayout(menu);

    QSplitter *up_bar = new QSplitter(Qt::Horizontal);
    up_bar->addWidget(logo);
    up_bar->addWidget(mode);
    up_bar->addWidget(actions);

    QSplitter *all = new QSplitter(Qt::Vertical);
    all->setStyleSheet("QSplitter::handle {"
                         "background: rgba(101, 104, 113, 235);"
                         "border: 0px solid #777;"
                         "height: 1px;"
                         "}");
    all->addWidget(up_bar);
    all->addWidget(main_area);

    QLayout *our = ui->centralWidget->layout();
//    ui->centralWidget->setLayout(propereties);
    our = new QHBoxLayout;
    our->addWidget(all);
    ui->centralWidget->setLayout(our);
}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::DCMode()
{
    qDebug() << "change mode";
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}

void MainGUIWindow::OMode()
{
    qDebug() << "change mode";
    ui->widget->SetMode(new ObjectMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}
