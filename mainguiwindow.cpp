#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{

    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(DCMode()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(OMode()));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    actions = new QWidget(this);
    actions->setLayout(new QHBoxLayout);
    allFigures = new QWidget(this);
    allFigures->setLayout(new QHBoxLayout);
    propereties = new QWidget(this);
    propereties->setLayout(new QHBoxLayout);
    listNew = new QWidget(this);
    listNew->setLayout(new QHBoxLayout);

    QLabel *logo = new QLabel("Q-ECD");
    logo->setStyleSheet("QLabel {"
                        "color: black;"
                        "background: white;"
                        "border: 4px solid #e8e235;"
                        "border-radius: 5px;"
                        "}");

    QSplitter *up_bar = new QSplitter(Qt::Horizontal);
    up_bar->addWidget(logo);
    up_bar->addWidget(actions);

    QSplitter *right_bar = new QSplitter(Qt::Vertical);
    right_bar->addWidget(allFigures);
    right_bar->addWidget(propereties);

    QSplitter *main_area = new QSplitter(Qt::Horizontal, this);
    main_area->addWidget(listNew);
    main_area->addWidget(ui->widget);
    main_area->addWidget(right_bar);

    QSplitter *all = new QSplitter(Qt::Vertical);
    all->setStyleSheet("QSplitter::handle {"
                             "background: transparent;"
                             "border: 0px solid #777;"
                             "height: 5px;"
                             "}");
    all->addWidget(up_bar);
    all->addWidget(main_area);

    qDebug() << "call set object mode";
    SetObjectMode();
    qDebug() << "finish setobj";

    QLayout *our = ui->centralWidget->layout();
    our = new QHBoxLayout;
    our->setMargin(0);
    our->addWidget(all);
    ui->centralWidget->setLayout(our);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::SetDrawCableMode()
{

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
void MainGUIWindow::SetObjectMode()
{
    QLayout *layout;

    layout = actions->layout();
    delete layout;

    layout = new QHBoxLayout;

    // set actions buttons
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
    // add actions button to up bar
//    menu->addWidget(mode);
    layout->addWidget(ui->pushButton);
    layout->addWidget(ui->pushButton_2);
    layout->addWidget(copy);
    layout->addWidget(pastle);
    layout->addWidget(deLete);
    layout->addWidget(rotateL);
    layout->addWidget(rotateR);
    layout->addItem(space);

    actions->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 4px solid #f03a73;"
                            "border-radius: 10px;"
                            "}");
    actions->setLayout(layout);

    layout = listNew->layout();
    delete layout;
    layout = new QVBoxLayout;

    QListWidget *list_new = new QListWidget;
    connect(list_new, SIGNAL(currentRowChanged(int)), ui->widget, SLOT(CreateFigure(int)));
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
    layout->addWidget(list_new);
    layout->setMargin(0);
    listNew->setStyleSheet("QWidget {"
                             "background-color: transparent;"
                             "border: 0px;"
                             "}");
    listNew->setLayout(layout);

    layout = propereties->layout();
    delete layout;
    layout = new QVBoxLayout;

    QLineEdit *info = new QLineEdit("bleh bleh bleh");
    QLineEdit *name = new QLineEdit("name bleh bleh");
    QLineEdit *var = new QLineEdit("var bleh bleh");
    QSpacerItem *space_up = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    layout->addWidget(info);
    layout->addWidget(name);
    layout->addWidget(var);
    layout->addItem(space_up);

    propereties->setStyleSheet("QWidget {"
                              "color: black;"
                              "background: white;"
                              "border: 4px solid #f03a73;"
                              "border-radius: 10px;"
                              "}");
    propereties->setLayout(layout);

    layout = allFigures->layout();
    delete layout;
    layout = new QVBoxLayout;

    QLabel *res = new QLabel("resistor");
    QLabel *cap = new QLabel("capasitor");
    QSpacerItem *space_up2 = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    layout->addWidget(res);
    layout->addWidget(cap);
    layout->addItem(space_up2);

    allFigures->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 4px solid #f5202a;"
                            "border-radius: 10px;"
                            "}");
    allFigures->setLayout(layout);
}
