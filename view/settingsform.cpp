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

    QPushButton *backgroundBarButton = new QPushButton("");

    QPushButton *borderBarButton = new QPushButton("");

    QPushButton *textColorBarButton = new QPushButton("");

    QVBoxLayout *page = new QVBoxLayout;
    page->addWidget(backgroundBarButton);

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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(page);
    layout->addLayout(result);

    connect(apply, SIGNAL(clicked()), this, SLOT(ApplySettings()));
    connect(ok, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(cansel, SIGNAL(clicked()), this, SLOT(Cancel()));

    this->setLayout(layout);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");
}

QLayout *SettingsForm::CreateButtonParamenter(QString text, QList<QWidget *> parameters)
{
    QLabel *itemText = new QLabel(text);
    QSpacerItem *space = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QHBoxLayout *settingItem = new QHBoxLayout;
    settingItem->addWidget(itemText);
    settingItem->addItem(space);
    QListIterator<QWidget *> it(parameters);
    while (it.hasNext())
    {
        settingItem->addWidget(it.next());
    }
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
