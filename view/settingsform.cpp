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

    

    // this->setLayout(layout);
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
