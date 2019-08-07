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
    right_down->setStyleSheet("QWidget {"
                              "color: black;"
                              "background: white;"
                              "border: 4px solid #f03a73;"
                              "border-radius: 10px;"
                              "}");
    right_down->setLayout(propereties);

    QLabel *res = new QLabel("resistor");
    QLabel *cap = new QLabel("capasitor");
    QSpacerItem *space_up2 = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    QVBoxLayout *list = new QVBoxLayout;
    list->addWidget(res);
    list->addWidget(cap);
    list->addItem(space_up2);

    QWidget *right_up = new QWidget;
    right_up->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 4px solid #f5202a;"
                            "border-radius: 10px;"
                            "}");
    right_up->setLayout(list);

    QSplitter *right_bar = new QSplitter(Qt::Vertical);
    right_bar->addWidget(right_up);
    right_bar->addWidget(right_down);

    QListWidget *list_new = new QListWidget;
    list_new->setStyleSheet("QListWidget{"
                            "border: 4px solid #67d43f;"
                            "border-radius: 10px;"
                            "background: white;"
                            "color: black;"
                            "selection-background-color: darkgray;"
                            "font-size: 20px; }"
                            "QListWidget { show-decoration-selected: 1; }"
                            "QListWidget::item:alternate { background: red; }"
                            "QListWidget::item:selected { color: black; border: none; }"
                            "QListWidget::item:selected:!active { background: rgb(150, 150, 150); }"
                            "QListWidget::item:selected:active { background: #b2c8eb; }"
                            "QListWidget::item:hover { background: #f095ee; }");
    QListWidgetItem *resistor = new QListWidgetItem(QIcon(":/figures/icons/figures/resistor.svg"), "Resistor", list_new);
    QListWidgetItem *capasitor = new QListWidgetItem(QIcon(":/figures/icons/figures/capasitor.svg"), "Capasitor", list_new);
    list_new->insertItem(0, resistor);
    list_new->insertItem(0, capasitor);
    QVBoxLayout *obj_mode = new QVBoxLayout;
    obj_mode->addWidget(list_new);
    obj_mode->setMargin(0);
    QWidget *left_bar = new QWidget;
    left_bar->setStyleSheet("QWidget {"
                             "background-color: transparent;"
                             "border: 0px;"
                             "}");
    left_bar->setLayout(obj_mode);

    QSplitter *main_area = new QSplitter(Qt::Horizontal);
    main_area->addWidget(left_bar);
    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    main_area->addWidget(ui->widget);
    main_area->addWidget(right_bar);

//    ui->widget->setStyleSheet("QWidget { border-radius: 10px; border: 4px solid #67d43f; }");

    QLabel *logo = new QLabel("Q-ECD");
    logo->setStyleSheet("QLabel {"
                        "color: black;"
                        "background: white;"
                        "border: 4px solid #e8e235;"
                        "border-radius: 5px;"
                        "}");
    QComboBox *mode = new QComboBox;
    mode->addItem("object");
    mode->addItem("draw cable");
    mode->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QPushButton *copy = new QPushButton("");
    copy->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    copy->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon copyIcon(QPixmap((":/objectmode/icons/objectmode/copy.svg")));
    copy->setIcon(copyIcon);
    copy->setIconSize(QSize(27, 27));
    copy->setFixedSize(40, 40);

    QPushButton *pastle = new QPushButton("");
    pastle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    pastle->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon pastleIcon(QPixmap((":/objectmode/icons/objectmode/pastle.svg")));
    pastle->setIcon(pastleIcon);
    pastle->setIconSize(QSize(27, 27));
    pastle->setFixedSize(40, 40);

    QPushButton *deLete = new QPushButton("");
    deLete->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    deLete->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon deleteIcon(QPixmap((":/objectmode/icons/objectmode/delete.svg")));
    deLete->setIcon(deleteIcon);
    deLete->setIconSize(QSize(27, 27));
    deLete->setFixedSize(40, 40);

    QPushButton *rotateL = new QPushButton("");
    rotateL->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    rotateL->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon rotateLIcon(QPixmap((":/objectmode/icons/objectmode/rotate_left.svg")));
    rotateL->setIcon(rotateLIcon);
    rotateL->setIconSize(QSize(27, 27));
    rotateL->setFixedSize(40, 40);

    QPushButton *rotateR = new QPushButton("");
    rotateR->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    rotateR->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon rotateRIcon(QPixmap((":/objectmode/icons/objectmode/rotate_right.svg")));
    rotateR->setIcon(rotateRIcon);
    rotateR->setIconSize(QSize(27, 27));
    rotateR->setFixedSize(40, 40);

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QHBoxLayout *menu = new QHBoxLayout;
    menu->addWidget(mode);
    menu->addWidget(ui->pushButton);
    menu->addWidget(ui->pushButton_2);
    menu->addWidget(copy);
    menu->addWidget(pastle);
    menu->addWidget(deLete);
    menu->addWidget(rotateL);
    menu->addWidget(rotateR);
    menu->addItem(space);

    QWidget *actions = new QWidget;
    actions->setStyleSheet("QWidget {"
                           "color: black;"
                           "background: white;"
                           "border: 4px solid #6e4ab5;"
                           "border-radius: 10px;"
                           "}");
    actions->setLayout(menu);

    QSplitter *up_bar = new QSplitter(Qt::Horizontal);
    up_bar->addWidget(logo);
    up_bar->addWidget(actions);

    QSplitter *all = new QSplitter(Qt::Vertical);
    all->setStyleSheet("QSplitter::handle {"
                             "background: transparent;"
                             "border: 0px solid #777;"
                             "height: 5px;"
                             "}");
    all->addWidget(up_bar);
    all->addWidget(main_area);

    QLayout *our = ui->centralWidget->layout();
//    ui->centralWidget->setStyleSheet("QWidget { background: transparent; }");
    our = new QHBoxLayout;
    our->setMargin(0);
    our->addWidget(all);
    ui->centralWidget->setLayout(our);
}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::DCMode()
{
    qDebug() << "change mode: drawcable";
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}

void MainGUIWindow::OMode()
{
    qDebug() << "change mode: object";
    ui->widget->SetMode(new ObjectMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
}
