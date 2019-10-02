#include "settingsform.h"
#include "ui_settingsform.h"
#include "mainguiwindow.h"
#include <QDebug>

SettingsForm::SettingsForm(MainGUIWindow *parent) : ui(new Ui::SettingsForm)
{
    Parent = parent;
    ui->setupUi(this);
    this->setWindowTitle("Settings");

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

    panels = new QTabWidget;
    ThemeSettings *pan = new ThemeSettings("");
    panels->addTab(pan, "Colors");
    panels->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ListFiguresSettings *list = new ListFiguresSettings("");
    panels->addTab(list, "List figures");
    panels->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(panels);
    layout->addItem(result);

    connect(apply, SIGNAL(clicked()), this, SLOT(ApplySettings()));
    connect(ok, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(cansel, SIGNAL(clicked()), this, SLOT(Cancel()));
    connect(this, SIGNAL(ReadSettings()), parent, SLOT(ReadSettings()));

    this->setLayout(layout);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::ApplySettings()
{
    int size =  panels->count();
    QWidget *current_panel;
    for (int i = 0; i < size; i++)
    {
        current_panel = panels->widget(i);
        emit current_panel->windowTitleChanged("");
    }
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
