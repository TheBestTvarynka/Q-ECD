#include "settingsform.h"
#include "ui_settingsform.h"
#include "mainguiwindow.h"
#include <QDebug>

SettingsForm::SettingsForm(QStyleSheetString *bar, QStyleSheetString *button, MainGUIWindow *parent) : QWidget(nullptr), ui(new Ui::SettingsForm)
{
    Parent = parent;
    ui->setupUi(this);
    this->setWindowTitle("Settings");

    barStyle = bar;
    buttonStyle = button;

    QLabel *title = new QLabel("Color theme settings");

    QHBoxLayout *result = new QHBoxLayout;
    QSpacerItem *result_space = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QPushButton *cansel = new QPushButton("Cancel");
    cansel->setStyleSheet(buttonStyle->GetStyleSheet());
    cansel->setFixedSize(120, 35);
    buttons.append(cansel);
    QPushButton *apply = new QPushButton("Apply changes");
    apply->setStyleSheet(buttonStyle->GetStyleSheet());
    apply->setFixedSize(120, 35);
    buttons.append(apply);
    QPushButton *ok = new QPushButton("Ok");
    ok->setStyleSheet(buttonStyle->GetStyleSheet());
    ok->setFixedSize(120, 35);
    buttons.append(ok);
    result->addItem(result_space);
    result->addWidget(cansel);
    result->addWidget(apply);
    result->addWidget(ok);
    result->setSpacing(15);

    QVBoxLayout *page = new QVBoxLayout;
    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    page->addWidget(title);
    page->addWidget(SetBarSettings());
    page->addWidget(SetButtonSettings());
    page->addItem(space);
    page->addItem(result);

    this->setLayout(page);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");

    connect(this, SIGNAL(UpdateStyle(QString, QString)), Parent, SLOT(UpdateStyle(QString, QString)));
    connect(apply, SIGNAL(clicked()), this, SLOT(ApplySettings()));
    connect(ok, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(cansel, SIGNAL(clicked()), this, SLOT(Cancel()));
}

QWidget *SettingsForm::SetBarSettings()
{
    QLabel *titleBar = new QLabel("Bars");
    titleBar->setStyleSheet("QLabel {"
                            "background: transparent;"
                            "color: black;"
                            "border: none; }");
    QList<QString> curBorder = barStyle->GetBorder();

    QLabel *bar_border_label = new QLabel("Border:");
    bar_border_label->setStyleSheet("QLabel {"
                                    "background: transparent;"
                                    "color: black;"
                                    "border: none; }");
    bar_border_size = new QSpinBox;
    bar_border_size->setMinimum(0);
    bar_border_size->setSingleStep(1);
    bar_border_size->setValue(curBorder[0].toInt());

    bar_border_color = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    bar_border_color->setStyleSheet(plainButton.GetStyleSheet());

    bar_border_radius = new QSpinBox;
    bar_border_radius->setMinimum(0);
    bar_border_radius->setSingleStep(1);
    bar_border_radius->setValue(curBorder[2].toInt());

    QLabel *bar_backgroud_label = new QLabel("Background:");
    bar_backgroud_label->setStyleSheet("QLabel {"
                                 "background: transparent;"
                                 "color: black;"
                                 "border: none; }");
    bar_background = new QPushButton("");
    plainButton.SetBackground(barStyle->GetBackground());
    bar_background->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *bar_border_layout = new QHBoxLayout;
    QSpacerItem *bar_border_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    bar_border_layout->addWidget(bar_border_label);
    bar_border_layout->addWidget(bar_border_size);
    bar_border_layout->addWidget(bar_border_color);
    bar_border_layout->addWidget(bar_border_radius);
    bar_border_layout->addItem(bar_border_space);
    bar_border_layout->setSpacing(15);
    QHBoxLayout *bar_background_layout = new QHBoxLayout;
    bar_background_layout->setSpacing(15);
    QSpacerItem *bar_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    bar_background_layout->addWidget(bar_backgroud_label);
    bar_background_layout->addWidget(bar_background);
    bar_background_layout->addItem(bar_background_space);

    QVBoxLayout *bar_settings = new QVBoxLayout;
    bar_settings->addWidget(titleBar);
    bar_settings->addItem(bar_border_layout);
    bar_settings->addItem(bar_background_layout);
    QWidget *bar = new QWidget;
    bars.append(bar);
    bar->setLayout(bar_settings);
    bar->setStyleSheet(barStyle->GetStyleSheet());

    connect(bar_border_color, SIGNAL(clicked()), this, SLOT(ClikedBarBorderColor()));
    connect(bar_border_size, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderSize(int)));
    connect(bar_border_radius, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderRadius(int)));
    connect(bar_background, SIGNAL(clicked()), this, SLOT(ClikedBarBackgroundColor()));

    return bar;
}

QWidget *SettingsForm::SetButtonSettings()
{
    QLabel *titleBar = new QLabel("Buttons");
    titleBar->setStyleSheet("QLabel {"
                            "background: transparent;"
                            "color: black;"
                            "border: none; }");
    QList<QString> curBorder = buttonStyle->GetBorder();

    QLabel *button_border_label = new QLabel("Border:");
    button_border_label->setStyleSheet("QLabel {"
                                       "background: transparent;"
                                       "color: black;"
                                       "border: none; }");
    button_border_size = new QSpinBox;
    button_border_size->setMinimum(0);
    button_border_size->setSingleStep(1);
    button_border_size->setValue(curBorder[0].toInt());

    button_border_color = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    button_border_color->setStyleSheet(plainButton.GetStyleSheet());

    button_border_radius = new QSpinBox;
    button_border_radius->setMinimum(0);
    button_border_radius->setSingleStep(1);
    button_border_radius->setValue(curBorder[2].toInt());

    QLabel *button_backgroud_label = new QLabel("Background:");
    button_backgroud_label->setStyleSheet("QLabel {"
                                          "background: transparent;"
                                          "color: black;"
                                          "border: none; }");
    button_background = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetBackground());
    button_background->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *button_hover_label = new QLabel("Hover:");
    button_hover_label->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_hover_color = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetHoverBackground());
    button_hover_color->setStyleSheet(plainButton.GetStyleSheet());

    QLabel *button_text_color_label = new QLabel("Hover:");
    button_text_color_label->setStyleSheet("QLabel {"
                                      "background: transparent;"
                                      "color: black;"
                                      "border: none; }");
    button_text_color = new QPushButton("");
    plainButton.SetBackground(buttonStyle->GetTextColor());
    button_text_color->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *button_border_layout = new QHBoxLayout;
    button_border_layout->setSpacing(15);
    QSpacerItem *button_border_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_border_layout->addWidget(button_border_label);
    button_border_layout->addWidget(button_border_size);
    button_border_layout->addWidget(button_border_color);
    button_border_layout->addWidget(button_border_radius);
    button_border_layout->addItem(button_border_space);

    QHBoxLayout *button_background_layout = new QHBoxLayout;
    button_background_layout->setSpacing(15);
    QSpacerItem *button_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_background_layout->addWidget(button_backgroud_label);
    button_background_layout->addWidget(button_background);
    button_background_layout->addItem(button_background_space);

    QHBoxLayout *button_hover_layout = new QHBoxLayout;
    button_hover_layout->setSpacing(15);
    QSpacerItem *button_hover_background_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_hover_layout->addWidget(button_hover_label);
    button_hover_layout->addWidget(button_hover_color);
    button_hover_layout->addItem(button_hover_background_space);

    QHBoxLayout *button_text_color_layout = new QHBoxLayout;
    button_text_color_layout->setSpacing(15);
    QSpacerItem *button_text_color_space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    button_text_color_layout->addWidget(button_text_color_label);
    button_text_color_layout->addWidget(button_text_color);
    button_text_color_layout->addItem(button_text_color_space);

    QVBoxLayout *button_settings = new QVBoxLayout;
    button_settings->addWidget(titleBar);
    button_settings->addItem(button_border_layout);
    button_settings->addItem(button_background_layout);
    button_settings->addItem(button_hover_layout);
    button_settings->addItem(button_text_color_layout);
    QWidget *button = new QWidget;
    bars.append(button);
    button->setLayout(button_settings);
    button->setStyleSheet(barStyle->GetStyleSheet());

    connect(button_border_color, SIGNAL(clicked()), this, SLOT(ClikedButtonBorderColor()));
    connect(button_border_size, SIGNAL(valueChanged(int)), this, SLOT(ChangedButtonBorderSize(int)));
    connect(button_border_radius, SIGNAL(valueChanged(int)), this, SLOT(ChangedButtonBorderRadius(int)));
    connect(button_background, SIGNAL(clicked()), this, SLOT(ClikedButtonBackgroundColor()));
    connect(button_hover_color, SIGNAL(clicked()), this, SLOT(ClikedButtonHoverBackgroundColor()));
    connect(button_text_color, SIGNAL(clicked()), this, SLOT(ClikedButtonTextColor()));
    return button;
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::ApplySettings()
{
    foreach (QWidget *i, bars)
    {
        i->setStyleSheet(barStyle->GetStyleSheet());
    }
    foreach (QPushButton *i, buttons)
    {
        i->setStyleSheet(buttonStyle->GetStyleSheet());
    }
    emit UpdateStyle(barStyle->GetStyleSheet(), buttonStyle->GetStyleSheet());
}

void SettingsForm::ClikedBarBorderColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(bar_border_color->styleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor barColor = color->GetColor();
    delete color;
    if (!barColor.isValid())
        return;
    str.SetBackground(barColor.name());
    bar_border_color->setStyleSheet(str.GetStyleSheet());

    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(border[0], barColor.name(), border[2]);
}

void SettingsForm::ClikedBarBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(barStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor barColor = color->GetColor();
    delete color;
    if (!barColor.isValid())
        return;
    barStyle->SetBackground(barColor.name());
    str.SetStyleSheet(bar_background->styleSheet());
    str.SetBackground(barColor.name());
    bar_background->setStyleSheet(str.GetStyleSheet());
}

void SettingsForm::ChangedBarBorderSize(int size)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(QString::number(size), border[1], border[2]);
}

void SettingsForm::ChangedBarBorderRadius(int radius)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(border[0], border[1], QString::number(radius));
}

void SettingsForm::ClikedButtonBorderColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(button_border_color->styleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    str.SetBackground(buttonColor.name());
    button_border_color->setStyleSheet(str.GetStyleSheet());

    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(border[0], buttonColor.name(), border[2]);
}

void SettingsForm::ClikedButtonBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetBackground(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_background->setStyleSheet(str.GetStyleSheet());
}

void SettingsForm::ClikedButtonHoverBackgroundColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetHoverBackground());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetHoverBackground(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_hover_color->setStyleSheet(str.GetStyleSheet());
}

void SettingsForm::ClikedButtonTextColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(buttonStyle->GetStyleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetTextColor());
    QColor buttonColor = color->GetColor();
    delete color;
    if (!buttonColor.isValid())
        return;
    buttonStyle->SetTextColor(buttonColor.name());
    str.SetStyleSheet(button_background->styleSheet());
    str.SetBackground(buttonColor.name());
    button_text_color->setStyleSheet(str.GetStyleSheet());
}

void SettingsForm::ChangedButtonBorderSize(int size)
{
    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(QString::number(size), border[1], border[2]);
}

void SettingsForm::ChangedButtonBorderRadius(int radius)
{
    QList<QString> border = buttonStyle->GetBorder();
    buttonStyle->SetBorder(border[0], border[1], QString::number(radius));
}

void SettingsForm::Cancel()
{
    this->close();
}

void SettingsForm::Ok()
{
    ApplySettings();
    Cancel();
}
