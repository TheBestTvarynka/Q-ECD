#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{
    ui->setupUi(this);

    actions = new QWidget(this);
    actions->setLayout(new QHBoxLayout);

    allFigures = new QWidget(this);
    QTree *tree = new QTree(allFigures);
    connect(ui->widget, SIGNAL(AddToTree(FigureInterface *)), tree, SLOT(CteateFigureItem(FigureInterface *)));
    connect(tree, SIGNAL(SetCurrentFigure(FigureInterface *)), ui->widget, SLOT(SetSelectedFigure(FigureInterface *)));
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(tree);
    allFigures->setLayout(l);

    propereties = new QWidget(this);
    QLayout *layout = new QVBoxLayout;

    QLayout *name_parameter = new QHBoxLayout;
    QLineEdit *name_line = new QLineEdit("");
    name = name_line;
    QLabel *name_label = new QLabel("name");
    name_parameter->addWidget(name_label);
    name_parameter->addWidget(name_line);

    QLayout *value_parameter = new QHBoxLayout;
    QLineEdit *value_line = new QLineEdit("");
    value = value_line;
    QLabel *value_label = new QLabel("value");
    value_parameter->addWidget(value_label);
    value_parameter->addWidget(value_line);
    QSpacerItem *space_up = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    layout->addItem(name_parameter);
    layout->addItem(value_parameter);
    layout->addItem(space_up);

    propereties->setStyleSheet("QWidget {"
                              "color: black;"
                              "background: white;"
                              "border: 4px solid #f03a73;"
                              "border-radius: 10px;"
                              "}");
    propereties->setLayout(layout);

    listNew = new QWidget(this);
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

    modes = new QWidget(this);
    modes->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 4px solid #3d66e0;"
                            "border-radius: 10px;"
                            "}");

    QLabel *logo = new QLabel("Q-ECD");
    logo->setStyleSheet("QLabel {"
                        "color: black;"
                        "background: white;"
                        "border: 4px solid #e8e235;"
                        "border-radius: 5px;"
                        "}");

    QPushButton *setObjectMode = new QPushButton("Object Mode");
    setObjectMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setObjectMode->setStyleSheet("QPushButton {"
                                 "background-color: white;"
                                 "border: 2px solid #67d43f;"
                                 "border-radius: 5px;"
                                 "color: black; }"
                                 "QPushButton::hover {"
                                 "background-color: #f24bef;"
                                 "color: #585957; }");

    QPushButton *setDrawCableMode = new QPushButton("Draw Cable Mode");
    setDrawCableMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setDrawCableMode->setStyleSheet("QPushButton {"
                                 "background-color: white;"
                                 "border: 2px solid #67d43f;"
                                 "border-radius: 5px;"
                                 "color: black; }"
                                 "QPushButton::hover {"
                                 "background-color: #f24bef;"
                                 "color: #585957; }");

    connect(setDrawCableMode, SIGNAL(clicked()), this, SLOT(SetDrawCableMode()));
    connect(setObjectMode, SIGNAL(clicked()), this, SLOT(SetObjectMode()));

    QHBoxLayout *swapModes = new QHBoxLayout;
    swapModes->addWidget(setObjectMode);
    swapModes->addWidget(setDrawCableMode);
    modes->setLayout(swapModes);

    QSplitter *up_bar = new QSplitter(Qt::Horizontal);
    up_bar->addWidget(logo);
    up_bar->addWidget(modes);
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

    SetObjectMode();

    QLayout *our = ui->centralWidget->layout();
    our = new QHBoxLayout;
    our->setMargin(0);
    our->addWidget(all);
    ui->centralWidget->setLayout(our);

    connect(ui->widget, SIGNAL(LoadFigurePropereties(QString, QString)), this, SLOT(LoadPropereties(QString, QString)));
    connect(ui->widget, SIGNAL(ClearPropereties()), this, SLOT(ClearPropereties()));
    connect(name, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(SetNameSelectedFigure(const QString &)));
    connect(value, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(SetValueSelectedFigure(const QString &)));
}

void MainGUIWindow::keyPressEvent(QKeyEvent *event)
{
    ui->widget->keyPressEvent(event);
}

void MainGUIWindow::keyReleaseEvent(QKeyEvent *event)
{
    ui->widget->keyReleaseEvent(event);
}

MainGUIWindow::~MainGUIWindow()
{
    delete ui;
}

void MainGUIWindow::ClearLayout(QLayout *layout)
{
    if (!layout)
        return;
    while (auto item = layout->takeAt(0))
    {
        delete item->widget();
        ClearLayout(item->layout());
    }
}

void MainGUIWindow::SetDrawCableMode()
{
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
    QLayout *layout;

    layout = actions->layout();
    ClearLayout(layout);

    QPushButton *newCable = new QPushButton("");
    newCable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    newCable->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon newIcon(QPixmap((":/drawcablemode/icons/drawcablemode/add_cable.svg")));
    newCable->setIcon(newIcon);
    newCable->setIconSize(QSize(27, 27));
    newCable->setFixedSize(40, 40);

    QPushButton *movePoint = new QPushButton("");
    movePoint->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    movePoint->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon movePIcon(QPixmap((":/drawcablemode/icons/drawcablemode/move_point.svg")));
    movePoint->setIcon(movePIcon);
    movePoint->setIconSize(QSize(27, 27));
    movePoint->setFixedSize(40, 40);

    QPushButton *moveEdge = new QPushButton("");
    moveEdge->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    moveEdge->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon moveEIcon(QPixmap((":/drawcablemode/icons/drawcablemode/move_edge.svg")));
    moveEdge->setIcon(moveEIcon);
    moveEdge->setIconSize(QSize(27, 27));
    moveEdge->setFixedSize(40, 40);

    QPushButton *selectCable = new QPushButton("");
    selectCable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    selectCable->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon selectCIcon(QPixmap((":/drawcablemode/icons/drawcablemode/select_cables.svg")));
    selectCable->setIcon(selectCIcon);
    selectCable->setIconSize(QSize(27, 27));
    selectCable->setFixedSize(40, 40);
    connect(selectCable, SIGNAL(clicked()), ui->widget, SLOT(SetRemoveCableMode()));

    QPushButton *removeCables = new QPushButton("");
    removeCables->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    removeCables->setStyleSheet("QPushButton {"
                        "background-color: white;"
                        "border: 2px solid #67d43f;"
                        "border-radius: 5px;"
                        "color: white;"
                        "padding: 15px 32px; }"
                        "QPushButton::hover {"
                        "background-color: #f24bef;"
                        "color: #585957; }");
    QIcon removeCIcon(QPixmap((":/drawcablemode/icons/drawcablemode/remove_cables.svg")));
    removeCables->setIcon(removeCIcon);
    removeCables->setIconSize(QSize(27, 27));
    removeCables->setFixedSize(40, 40);
    connect(removeCables, SIGNAL(clicked()), ui->widget, SLOT(RemoveSelectedCables()));

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(newCable);
    layout->addWidget(movePoint);
    layout->addWidget(moveEdge);
    layout->addWidget(selectCable);
    layout->addWidget(removeCables);
    layout->addItem(space);

    actions->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 4px solid #f03a73;"
                            "border-radius: 10px;"
                            "}");

    listNew->setEnabled(false);
    allFigures->setEnabled(false);
    propereties->setEnabled(false);
}
void MainGUIWindow::SetObjectMode()
{
    ui->widget->SetMode(new ObjectMode(ui->widget, ui->widget->GetScale(), ui->widget->GetCenter(), ui->widget->width(), ui->widget->height()));
    QLayout *layout;

    layout = actions->layout();
    ClearLayout(layout);

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
    connect(copy, SIGNAL(clicked()), ui->widget, SLOT(CopySelectedFigure()));

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
    connect(pastle, SIGNAL(clicked()), ui->widget, SLOT(PasteFromBuffer()));

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
    connect(deLete, SIGNAL(clicked()), ui->widget, SLOT(RemoveSelectedFigure()));

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
    connect(rotateL, SIGNAL(clicked()), ui->widget, SLOT(RotateSelectedFigureLeft()));

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
    connect(rotateR, SIGNAL(clicked()), ui->widget, SLOT(RotateSelectedFigureRight()));

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
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

    allFigures->setStyleSheet("QWidget {"
                            "color: black;"
                            "background: white;"
                            "border: 0px solid #f5202a;"
                            "border-radius: 10px;"
                            "}");

    listNew->setEnabled(true);
    allFigures->setEnabled(true);
    propereties->setEnabled(true);
}

void MainGUIWindow::LoadPropereties(QString n, QString v)
{
    name->setText(n);
    value->setText(v);
}

void MainGUIWindow::ClearPropereties()
{
    name->clear();
    value->clear();
}
