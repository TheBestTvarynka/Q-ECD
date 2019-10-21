#include "settingsform.h"
#include "ui_settingsform.h"
#include "mainguiwindow.h"
#include <QDebug>

SettingsForm::SettingsForm(MainGUIWindow *parent) : ui(new Ui::SettingsForm)
{
    PATH = "/home/qkation/.config/q-ecd/theme/";
    Parent = parent;
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    LoadSettings();

    QHBoxLayout *result = new QHBoxLayout;
    QSpacerItem *result_space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QPushButton *cansel = new QPushButton("Cancel");
    cansel->setStyleSheet(buttonStyle->GetStyleSheet());
    cansel->setFixedSize(120, 35);
    QPushButton *apply = new QPushButton("Apply changes");
    apply->setStyleSheet(buttonStyle->GetStyleSheet());
    apply->setFixedSize(120, 35);
    QPushButton *ok = new QPushButton("Ok");
    ok->setStyleSheet(buttonStyle->GetStyleSheet());
    ok->setFixedSize(120, 35);
    result->addItem(result_space);
    result->addWidget(cansel);
    result->addWidget(apply);
    result->addWidget(ok);
    result->setSpacing(15);

    QScrollArea *baseSettings = new QScrollArea;
    baseSettings->setWidget(CreateForm());
    baseSettings->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(baseSettings);
    layout->addLayout(result);

    connect(apply, SIGNAL(clicked()), this, SLOT(ApplySettings()));
    connect(ok, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(cansel, SIGNAL(clicked()), this, SLOT(Cancel()));

    this->setLayout(layout);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");
}

QColor SettingsForm::SelectColor(QString startColor)
{
    QColorDialogWindow *color = new QColorDialogWindow(startColor);
    QColor barColor = color->GetColor();
    delete color;
    return  barColor;
}

QWidget *SettingsForm::CreateForm()
{
    colorSelectors["Bar background color"] = new QChooseColorButton(barStyle->GetPropereties("", "background"));
    colorSelectors["Bar border-radius"] = new QChooseNumberBox(barStyle->GetPropereties("", "borer-radius").toInt());
    colorSelectors["Bar border-width"] = new QChooseNumberBox(barStyle->GetPropereties("", "borer-width").toInt());
    colorSelectors["Bar border-color"] = new QChooseColorButton(barStyle->GetPropereties("", "border-color"));
    colorSelectors["Bar text color"] = new QChooseColorButton(barStyle->GetPropereties("", "color"));

    QVBoxLayout *barLayout = new QVBoxLayout;
    barLayout->addLayout(CreateOptionLine("Background color", (QChooseColorButton *)colorSelectors["Bar background color"]));
    barLayout->addLayout(CreateOptionLine("Border-radius", (QChooseNumberBox *)colorSelectors["Bar border-radius"]));
    barLayout->addLayout(CreateOptionLine("Border-width", (QChooseNumberBox *)colorSelectors["Bar border-width"]));
    barLayout->addLayout(CreateOptionLine("Border-color", (QChooseNumberBox *)colorSelectors["Bar border-color"]));
    barLayout->addLayout(CreateOptionLine("Text color", (QChooseNumberBox *)colorSelectors["Bar text color"]));
    QWidget *barWidget = new QWidget;
    barWidget->setLayout(barLayout);
    barWidget->setStyleSheet(barStyle->GetStyleSheet());

    colorSelectors["Button background color"] = new QChooseColorButton(buttonStyle->GetPropereties("", "background"));
    colorSelectors["Button border-radius"] = new QChooseNumberBox(buttonStyle->GetPropereties("", "borer-radius").toInt());
    colorSelectors["Button border-width"] = new QChooseNumberBox(buttonStyle->GetPropereties("", "borer-width").toInt());
    colorSelectors["Button border-color"] = new QChooseColorButton(buttonStyle->GetPropereties("", "border-color"));
    colorSelectors["Button text color"] = new QChooseColorButton(buttonStyle->GetPropereties("", "color"));

    colorSelectors["Button hover background color"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "background"));
    colorSelectors["Button hover border-radius"] = new QChooseNumberBox(buttonStyle->GetPropereties("::hover", "borer-radius").toInt());
    colorSelectors["Button hover border-width"] = new QChooseNumberBox(buttonStyle->GetPropereties("::hover", "borer-width").toInt());
    colorSelectors["Button hover border-color"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "border-color"));
    colorSelectors["Button hover text color"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "color"));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addLayout(CreateOptionLine("Background color", (QChooseColorButton *)colorSelectors["Button background color"]));
    buttonLayout->addLayout(CreateOptionLine("Border-radius", (QChooseNumberBox *)colorSelectors["Button border-radius"]));
    buttonLayout->addLayout(CreateOptionLine("Border-width", (QChooseNumberBox *)colorSelectors["Button border-width"]));
    buttonLayout->addLayout(CreateOptionLine("Border-color", (QChooseNumberBox *)colorSelectors["Button border-color"]));
    buttonLayout->addLayout(CreateOptionLine("Text color", (QChooseNumberBox *)colorSelectors["Button text color"]));

    buttonLayout->addLayout(CreateOptionLine("Background hover color", (QChooseColorButton *)colorSelectors["Button hover background color"]));
    buttonLayout->addLayout(CreateOptionLine("Border-radius hover", (QChooseNumberBox *)colorSelectors["Button hover border-radius"]));
    buttonLayout->addLayout(CreateOptionLine("Border-width hover", (QChooseNumberBox *)colorSelectors["Button hover border-width"]));
    buttonLayout->addLayout(CreateOptionLine("Border-color hover", (QChooseNumberBox *)colorSelectors["Button hover border-color"]));
    buttonLayout->addLayout(CreateOptionLine("Text color hover", (QChooseNumberBox *)colorSelectors["Button hover text color"]));
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet(barStyle->GetStyleSheet());

    colorSelectors["List background"] = new QChooseColorButton(listNewStyle->GetPropereties("", "background"));
    colorSelectors["List text color"] = new QChooseColorButton(listNewStyle->GetPropereties("", "color"));
    colorSelectors["List selection-background-color"] = new QChooseColorButton(listNewStyle->GetPropereties("", "selection-background-color"));
    colorSelectors["List background item alternate"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:alternate", "background"));
    colorSelectors["List background item selected"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected", "background"));
    colorSelectors["List background item selected active"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected:!active", "background"));
    colorSelectors["List background item selected !active"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected:active", "background"));
    colorSelectors["List background item hover"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:hover", "background"));

    QVBoxLayout *listNewLayout = new QVBoxLayout;
    listNewLayout->addLayout(CreateOptionLine("List background color", (QChooseColorButton *)colorSelectors["List background"]));
    listNewLayout->addLayout(CreateOptionLine("List text color", (QChooseColorButton *)colorSelectors["List text color"]));
    listNewLayout->addLayout(CreateOptionLine("List selection-background-color", (QChooseColorButton *)colorSelectors["List selection-background-color"]));
    listNewLayout->addLayout(CreateOptionLine("List background item alternate color", (QChooseColorButton *)colorSelectors["List background item alternate"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected color", (QChooseColorButton *)colorSelectors["List background item selected"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected active color", (QChooseColorButton *)colorSelectors["List background item selected active"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected !active color", (QChooseColorButton *)colorSelectors["List background item selected !active"]));
    listNewLayout->addLayout(CreateOptionLine("List background item hover color", (QChooseColorButton *)colorSelectors["List background item hover"]));
    QWidget *listNewWidget = new QWidget;
    listNewWidget->setLayout(listNewLayout);
    listNewWidget->setStyleSheet(barStyle->GetStyleSheet());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(barWidget);
    layout->addWidget(buttonWidget);
    layout->addWidget(listNewWidget);
    QWidget *pageSettings = new QWidget;
    pageSettings->setLayout(layout);

    return pageSettings;
}

QLayout *SettingsForm::CreateOptionLine(QString text, QWidget *parameter)
{
    QLabel *itemText = new QLabel(text);
    QSpacerItem *space = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QHBoxLayout *settingItem = new QHBoxLayout;
    settingItem->addWidget(itemText);
    settingItem->addItem(space);
    parameter->setFixedWidth(200);
    settingItem->addWidget(parameter);
    return settingItem;
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::LoadSettings()
{
    QFile bar_css(PATH + "barStyle.css");
    bar_css.open(QFile::ReadOnly);
    if (!bar_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    barStyle = new QStyleSheetString("QWidget");
    barStyle->SetStyleSheet(QLatin1String(bar_css.readAll()));
    bar_css.close();

    QFile button_css(PATH + "buttonStyle.css");
    button_css.open(QFile::ReadOnly);
    if (!button_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    buttonStyle = new QStyleSheetString("QPushButton");
    buttonStyle->SetStyleSheet(QLatin1String(button_css.readAll()));
    button_css.close();

    QFile list_new_css(PATH + "listNew.css");
    list_new_css.open(QFile::ReadOnly);
    if (!list_new_css.isOpen())
    {
        qDebug() << "error: file not found";
    }
    listNewStyle = new QStyleSheetString("QListWidget");
    listNewStyle->SetStyleSheet(QLatin1String(list_new_css.readAll()));
    list_new_css.close();
}

void SettingsForm::ApplySettings()
{
//    int size =  panels->count();
//    QWidget *current_panel;
//    for (int i = 0; i < size; i++)
//    {
//        current_panel = panels->widget(i);
//        emit current_panel->windowTitleChanged("");
//    }
//    emit ReadSettings();
}

void SettingsForm::Cancel()
{
    this->close();
}

void SettingsForm::Ok()
{
    ApplySettings();
    this->close();
}
