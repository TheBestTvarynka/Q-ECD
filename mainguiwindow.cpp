#include "mainguiwindow.h"
#include "ui_mainguiwindow.h"

MainGUIWindow::MainGUIWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGUIWindow)
{
    ui->setupUi(this);


    barStyle = new QStyleSheetString("QWidget");
    barStyle->SetBorder("2", "#1d7f88", "5");
    barStyle->SetBackground("#6ac7bc");
    barStyle->SetTextColor("#000000");
    barStyle->EraseBlock("QWidget::hover");

    buttonStyle = new QStyleSheetString("QPushButton");
    buttonStyle->SetBorder("2", "#67d43f", "5");
    buttonStyle->SetHoverBorder("2", "#1d7f88", "5");
    buttonStyle->SetBackground("#ffffff");
    buttonStyle->SetHoverBackground("#f24bef");
    buttonStyle->SetTextColor("#86ab29");

    actions = new QWidget(this);
    actions->setLayout(new QHBoxLayout);

    allFigures = new QWidget(this);
    QTree *tree = new QTree(allFigures);
    connect(ui->widget, SIGNAL(AddToTree(FigureInterface *)), tree, SLOT(CteateFigureItem(FigureInterface *)));
    connect(tree, SIGNAL(SetCurrentFigure(FigureInterface *)), ui->widget->GetDataFigures(), SLOT(SetSelectedFigure(FigureInterface *)));
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

    propereties->setStyleSheet(barStyle->GetStyleSheet());
    propereties->setLayout(layout);

    listNew = new QWidget(this);
    layout = new QVBoxLayout;
    QListWidget *list_new = new QListWidget;
    connect(list_new, SIGNAL(currentRowChanged(int)), ui->widget, SLOT(CreateFigure(int)));
    list_new->setStyleSheet("QListWidget{"
                            "border: none;"
//                            "border-radius: 5px;"
                            "background: #d0f3f7;"
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
    layout->setMargin(5);
    listNew->setStyleSheet(barStyle->GetStyleSheet());
    listNew->setLayout(layout);

    modes = new QWidget(this);
    modes->setStyleSheet(barStyle->GetStyleSheet());

    logo = new QLabel("Q-ECD");
//    logo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QStyleSheetString str(*barStyle);
    str.SetName("QLabel");
    logo->setStyleSheet(str.GetStyleSheet());

    QPushButton *setObjectMode = new QPushButton("Object Mode");
//    setObjectMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setObjectMode->setStyleSheet(buttonStyle->GetStyleSheet());
    setObjectMode->setFixedHeight(40);

    QPushButton *setDrawCableMode = new QPushButton("Draw Cable Mode");
//    setDrawCableMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setDrawCableMode->setStyleSheet(buttonStyle->GetStyleSheet());
    setDrawCableMode->setFixedHeight(40);

    connect(setDrawCableMode, SIGNAL(clicked()), this, SLOT(SetDrawCableMode()));
    connect(setObjectMode, SIGNAL(clicked()), this, SLOT(SetObjectMode()));

    QHBoxLayout *swapModes = new QHBoxLayout;
    swapModes->addWidget(setObjectMode);
    swapModes->addWidget(setDrawCableMode);
    swapModes->setMargin(5);
    modes->setLayout(swapModes);

    QSplitter *up_bar = new QSplitter(Qt::Horizontal);
//    up_bar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
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

    SetObjectMode();

    QSplitter *all = new QSplitter(Qt::Vertical);
    all->setStyleSheet("QSplitter::handle {"
                       "background: transparent;"
                       "border: 0px solid #777;"
                       "height: 2px;"
                       "}");
    all->addWidget(up_bar);
    all->addWidget(main_area);

    QLayout *our = ui->centralWidget->layout();
    our = new QHBoxLayout;
    our->setMargin(3);
    our->addWidget(all);
    ui->centralWidget->setLayout(our);
    ui->centralWidget->setStyleSheet("QWidget {"
                                     "background: white;"
                                     "border: none;"
                                     "}");
    connect(ui->widget, SIGNAL(LoadFigurePropereties(QString, QString)), this, SLOT(LoadPropereties(QString, QString)));
    connect(ui->widget->GetDataFigures(), SIGNAL(LoadFigurePropereties(QString, QString)), this, SLOT(LoadPropereties(QString, QString)));
    connect(ui->widget->GetDataFigures(), SIGNAL(ClearPropereties()), this, SLOT(ClearPropereties()));
    connect(name, SIGNAL(textChanged(const QString &)), ui->widget->GetDataFigures(), SLOT(SetNameSelectedFigure(const QString &)));
    connect(value, SIGNAL(textChanged(const QString &)), ui->widget->GetDataFigures(), SLOT(SetValueSelectedFigure(const QString &)));
    connect(ui->widget->GetDataFigures(), SIGNAL(RemoveCables(QList<IObserver *>)), ui->widget->GetDataCables(), SLOT(RemoveCables(QList<IObserver *>)));
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
    delete modes;
    delete actions;
    delete allFigures;
    delete propereties;
    delete listNew;
    delete barStyle;
    delete buttonStyle;
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
    ui->widget->SetMode(new DrawCableMode(ui->widget, ui->widget->GetScale()));
    QLayout *layout;

    layout = actions->layout();
    ClearLayout(layout);

    QPushButton *newCable = new QPushButton("");
    newCable->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon newIcon(QPixmap((":/drawcablemode/icons/drawcablemode/add_cable.svg")));
    newCable->setIcon(newIcon);
    newCable->setIconSize(QSize(27, 27));
    newCable->setMinimumSize(40, 40);

    QPushButton *movePoint = new QPushButton("");
    movePoint->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon movePIcon(QPixmap((":/drawcablemode/icons/drawcablemode/move_point.svg")));
    movePoint->setIcon(movePIcon);
    movePoint->setIconSize(QSize(27, 27));
    movePoint->setMinimumSize(40, 40);

    QPushButton *moveEdge = new QPushButton("");
    moveEdge->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon moveEIcon(QPixmap((":/drawcablemode/icons/drawcablemode/move_edge.svg")));
    moveEdge->setIcon(moveEIcon);
    moveEdge->setIconSize(QSize(27, 27));
    moveEdge->setMinimumSize(40, 40);

    QPushButton *selectCable = new QPushButton("");
    selectCable->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon selectCIcon(QPixmap((":/drawcablemode/icons/drawcablemode/select_cables.svg")));
    selectCable->setIcon(selectCIcon);
    selectCable->setIconSize(QSize(27, 27));
    selectCable->setMinimumSize(40, 40);
    connect(selectCable, SIGNAL(clicked()), ui->widget, SLOT(SetRemoveCableMode()));

    QPushButton *removeCables = new QPushButton("");
    removeCables->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon removeCIcon(QPixmap((":/drawcablemode/icons/drawcablemode/remove_cables.svg")));
    removeCables->setIcon(removeCIcon);
    removeCables->setIconSize(QSize(27, 27));
    removeCables->setMinimumSize(40, 40);
    connect(removeCables, SIGNAL(clicked()), ui->widget->GetDataCables(), SLOT(RemoveSelectedCables()));

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(newCable);
    layout->addWidget(movePoint);
    layout->addWidget(moveEdge);
    layout->addWidget(selectCable);
    layout->addWidget(removeCables);
    layout->addItem(space);
    layout->setMargin(5);

    actions->setStyleSheet(barStyle->GetStyleSheet());

    listNew->setEnabled(false);
    allFigures->setEnabled(false);
    propereties->setEnabled(false);
}
void MainGUIWindow::SetObjectMode()
{
    ui->widget->SetMode(new ObjectMode(ui->widget, ui->widget->GetScale()));
    QLayout *layout;

    layout = actions->layout();
    ClearLayout(layout);

    QPushButton *copy = new QPushButton("");
    copy->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon copyIcon(QPixmap((":/objectmode/icons/objectmode/copy.svg")));
    copy->setIcon(copyIcon);
    copy->setIconSize(QSize(27, 27));
    copy->setMinimumSize(40, 40);
    connect(copy, SIGNAL(clicked()), ui->widget, SLOT(CopySelectedFigure()));

    QPushButton *pastle = new QPushButton("");
    pastle->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon pastleIcon(QPixmap((":/objectmode/icons/objectmode/pastle.svg")));
    pastle->setIcon(pastleIcon);
    pastle->setIconSize(QSize(27, 27));
    pastle->setMinimumSize(40, 40);
    connect(pastle, SIGNAL(clicked()), ui->widget, SLOT(PasteFromBuffer()));

    QPushButton *deLete = new QPushButton("");
    deLete->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon deleteIcon(QPixmap((":/objectmode/icons/objectmode/delete.svg")));
    deLete->setIcon(deleteIcon);
    deLete->setIconSize(QSize(27, 27));\
    deLete->setMinimumSize(40, 40);
    connect(deLete, SIGNAL(clicked()), ui->widget->GetDataFigures(), SLOT(RemoveSelectedFigure()));

    QPushButton *rotateL = new QPushButton("");
    rotateL->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon rotateLIcon(QPixmap((":/objectmode/icons/objectmode/rotate_left.svg")));
    rotateL->setIcon(rotateLIcon);
    rotateL->setIconSize(QSize(27, 27));
    rotateL->setMinimumSize(40, 40);
    connect(rotateL, SIGNAL(clicked()), ui->widget->GetDataFigures(), SLOT(RotateSelectedFigureLeft()));

    QPushButton *rotateR = new QPushButton("");
    rotateR->setStyleSheet(buttonStyle->GetStyleSheet());
    QIcon rotateRIcon(QPixmap((":/objectmode/icons/objectmode/rotate_right.svg")));
    rotateR->setIcon(rotateRIcon);
    rotateR->setIconSize(QSize(27, 27));
    rotateR->setMinimumSize(40, 40);
    connect(rotateR, SIGNAL(clicked()), ui->widget->GetDataFigures(), SLOT(RotateSelectedFigureRight()));

    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(copy);
    layout->addWidget(pastle);
    layout->addWidget(deLete);
    layout->addWidget(rotateL);
    layout->addWidget(rotateR);
    layout->addItem(space);
    layout->setMargin(5);

    actions->setStyleSheet(barStyle->GetStyleSheet());
    actions->setLayout(layout);

    allFigures->setStyleSheet(barStyle->GetStyleSheet());

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

void MainGUIWindow::on_actionSettings_triggered()
{
    SettingsForm *settings = new SettingsForm(barStyle, buttonStyle, this);
    settings->show();
}

void MainGUIWindow::UpdateStyle(QString bar, QString button)
{
    barStyle->SetStyleSheet(bar);
    modes->setStyleSheet(barStyle->GetStyleSheet());
    actions->setStyleSheet(barStyle->GetStyleSheet());
    allFigures->setStyleSheet(barStyle->GetStyleSheet());
    propereties->setStyleSheet(barStyle->GetStyleSheet());
    listNew->setStyleSheet(barStyle->GetStyleSheet());

    QStyleSheetString str(*barStyle);
    str.SetName("QLabel");
    logo->setStyleSheet(str.GetStyleSheet());

    QWidget *w;
    QLayout *act = actions->layout();
    for (int i = 0; i < act->count(); i++)
    {
        w = act->itemAt(i)->widget();
        if (w != nullptr)
            w->setStyleSheet(buttonStyle->GetStyleSheet());
    }
    act = modes->layout();
    for (int i = 0; i < act->count(); i++)
    {
        w = act->itemAt(i)->widget();
        if (w != nullptr)
            w->setStyleSheet(buttonStyle->GetStyleSheet());
    }
}
