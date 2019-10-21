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

QWidget *SettingsForm::CreateForm()
{
    qDebug() << "==========START========";

    barTheme[":background"] = new QChooseColorButton(barStyle->GetPropereties("", "background"));
    barTheme[":border-radius"] = new QChooseNumberBox(barStyle->GetPropereties("", "border-radius"));
    barTheme[":border-width"] = new QChooseNumberBox(barStyle->GetPropereties("", "border-width"));
    barTheme[":border-color"] = new QChooseColorButton(barStyle->GetPropereties("", "border-color"));
    barTheme[":color"] = new QChooseColorButton(barStyle->GetPropereties("", "color"));

    QVBoxLayout *barLayout = new QVBoxLayout;
    barLayout->addLayout(CreateOptionLine("Background color", (QChooseColorButton *)barTheme[":background"]));
    barLayout->addLayout(CreateOptionLine("Border-radius", (QChooseNumberBox *)barTheme[":border-radius"]));
    barLayout->addLayout(CreateOptionLine("Border-width", (QChooseNumberBox *)barTheme[":border-width"]));
    barLayout->addLayout(CreateOptionLine("Border-color", (QChooseColorButton *)barTheme[":border-color"]));
    barLayout->addLayout(CreateOptionLine("Text color", (QChooseColorButton *)barTheme[":color"]));
    QWidget *barWidget = new QWidget;
    barWidget->setLayout(barLayout);
    barWidget->setStyleSheet(barStyle->GetStyleSheet());

    buttonsTheme[":background"] = new QChooseColorButton(buttonStyle->GetPropereties("", "background"));
    buttonsTheme[":border-radius"] = new QChooseNumberBox(buttonStyle->GetPropereties("", "border-radius"));
    buttonsTheme[":border-width"] = new QChooseNumberBox(buttonStyle->GetPropereties("", "border-width"));
    buttonsTheme[":border-color"] = new QChooseColorButton(buttonStyle->GetPropereties("", "border-color"));
    buttonsTheme[":color"] = new QChooseColorButton(buttonStyle->GetPropereties("", "color"));

    buttonsTheme["hover:background"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "background"));
    buttonsTheme["hover:border-radius"] = new QChooseNumberBox(buttonStyle->GetPropereties("::hover", "border-radius"));
    buttonsTheme["hover:border-width"] = new QChooseNumberBox(buttonStyle->GetPropereties("::hover", "border-width"));
    buttonsTheme["hover:border-color"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "border-color"));
    buttonsTheme["hover:color"] = new QChooseColorButton(buttonStyle->GetPropereties("::hover", "color"));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addLayout(CreateOptionLine("Background color", (QChooseColorButton *)buttonsTheme[":background"]));
    buttonLayout->addLayout(CreateOptionLine("Border-radius", (QChooseNumberBox *)buttonsTheme[":border-radius"]));
    buttonLayout->addLayout(CreateOptionLine("Border-width", (QChooseNumberBox *)buttonsTheme[":border-width"]));
    buttonLayout->addLayout(CreateOptionLine("Border-color", (QChooseColorButton *)buttonsTheme[":border-color"]));
    buttonLayout->addLayout(CreateOptionLine("Text color", (QChooseColorButton *)buttonsTheme[":color"]));

    buttonLayout->addLayout(CreateOptionLine("Background hover color", (QChooseColorButton *)buttonsTheme["hover:background"]));
    buttonLayout->addLayout(CreateOptionLine("Border-radius hover", (QChooseNumberBox *)buttonsTheme["hover:border-radius"]));
    buttonLayout->addLayout(CreateOptionLine("Border-width hover", (QChooseNumberBox *)buttonsTheme["hover:border-width"]));
    buttonLayout->addLayout(CreateOptionLine("Border-color hover", (QChooseColorButton *)buttonsTheme["hover:border-color"]));
    buttonLayout->addLayout(CreateOptionLine("Text color hover", (QChooseColorButton *)buttonsTheme["hover:color"]));
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet(barStyle->GetStyleSheet());

    listNewTheme[":background"] = new QChooseColorButton(listNewStyle->GetPropereties("", "background"));
    listNewTheme[":color"] = new QChooseColorButton(listNewStyle->GetPropereties("", "color"));
    listNewTheme[":selection-background-color"] = new QChooseColorButton(listNewStyle->GetPropereties("", "selection-background-color"));
    listNewTheme["::item:alternate:background"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:alternate", "background"));
    listNewTheme["::item:selected:background"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected", "background"));
    listNewTheme["::item:selected:active:background"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected:!active", "background"));
    listNewTheme["::item:selected:!active:background"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:selected:active", "background"));
    listNewTheme["::item:hover:background"] = new QChooseColorButton(listNewStyle->GetPropereties("::item:hover", "background"));

    QVBoxLayout *listNewLayout = new QVBoxLayout;
    listNewLayout->addLayout(CreateOptionLine("List background color", (QChooseColorButton *)listNewTheme[":background"]));
    listNewLayout->addLayout(CreateOptionLine("List text color", (QChooseColorButton *)listNewTheme[":color"]));
    listNewLayout->addLayout(CreateOptionLine("List selection-background-color", (QChooseColorButton *)listNewTheme[":selection-background-color"]));
    listNewLayout->addLayout(CreateOptionLine("List background item alternate color", (QChooseColorButton *)listNewTheme["::item:alternate:background"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected color", (QChooseColorButton *)listNewTheme["::item:selected:background"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected active color", (QChooseColorButton *)listNewTheme["::item:selected:active:background"]));
    listNewLayout->addLayout(CreateOptionLine("List background item selected !active color", (QChooseColorButton *)listNewTheme["::item:selected:!active:background"]));
    listNewLayout->addLayout(CreateOptionLine("List background item hover color", (QChooseColorButton *)listNewTheme["::item:hover:background"]));
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
    QMapIterator<QString, ISetter *> itBar(barTheme);
    while (itBar.hasNext())
    {
        itBar.next();
        barStyle->SetPropereties(itBar.key(), itBar.value()->GetValue().toString());
    }
    QFile barThemeFile("/home/qkation/.config/q-ecd/theme/barStyle.css");
    barThemeFile.open(QIODevice::WriteOnly | QIODevice::Text);
    barThemeFile.write(barStyle->GetStyleSheet().toUtf8());
    barThemeFile.close();
    QMapIterator<QString, ISetter *> itButton(buttonsTheme);
    while (itButton.hasNext())
    {
        itButton.next();
        buttonStyle->SetPropereties(itButton.key(), itButton.value()->GetValue().toString());
    }
    QFile buttonThemeFile("/home/qkation/.config/q-ecd/theme/buttonStyle.css");
    buttonThemeFile.open(QIODevice::WriteOnly | QIODevice::Text);
    buttonThemeFile.write(buttonStyle->GetStyleSheet().toUtf8());
    buttonThemeFile.close();
    QMapIterator<QString, ISetter *> itListNew(listNewTheme);
    while (itListNew.hasNext())
    {
        itListNew.next();
        listNewStyle->SetPropereties(itListNew.key(), itListNew.value()->GetValue().toString());
    }
    QFile listNewThemeFile("/home/qkation/.config/q-ecd/theme/listNew.css");
    listNewThemeFile.open(QIODevice::WriteOnly | QIODevice::Text);
    listNewThemeFile.write(listNewStyle->GetStyleSheet().toUtf8());
    listNewThemeFile.close();
    emit ReadSettings();
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
