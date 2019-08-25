#include "settingsform.h"
#include "ui_settingsform.h"
#include "mainguiwindow.h"
#include <QDebug>

SettingsForm::SettingsForm(QStyleSheetString *bar, QStyleSheetString *button, MainGUIWindow *parent) : QWidget(nullptr), ui(new Ui::SettingsForm)
{
    Parent = parent;
    ui->setupUi(this);

    barStyle = bar;
    buttonStyle = button;

    QLabel *title = new QLabel("Color theme settings");

    QLabel *titleBar = new QLabel("Bars");
    QList<QString> curBorder = bar->GetBorder();

    QLabel *borderBar = new QLabel("Border:");
    borderBar->setStyleSheet("QLabel {"
                             "background: transparent;"
                             "color: black;"
                             "border: none; }");
    QSpinBox *sizeBar = new QSpinBox;
    sizeBar->setMinimum(0);
    sizeBar->setSingleStep(1);
    sizeBar->setValue(curBorder[0].toInt());
    borderSizeBar = sizeBar;

    QPushButton *colorBorderBar = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("2", "#ffffff", "2");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    colorBorderBar->setStyleSheet(plainButton.GetStyleSheet());
    borderColorBar = colorBorderBar;

    QSpinBox *radiusBar = new QSpinBox;
    radiusBar->setMinimum(0);
    radiusBar->setSingleStep(1);
    radiusBar->setValue(curBorder[2].toInt());
    borderRadiusBar = radiusBar;
//    radiusBar->setDisplayIntegerBase(curBorder[2].toInt());

    QLabel *backgroundBar = new QLabel("Background:");
    backgroundBar->setStyleSheet("QLabel {"
                                 "background: transparent;"
                                 "color: black;"
                                 "border: none; }");
    QPushButton *colorBackgroundBar = new QPushButton("");
    plainButton.SetBackground(bar->GetBackground());
    colorBackgroundBar->setStyleSheet(plainButton.GetStyleSheet());
    backgroundColorBar = colorBackgroundBar;

    QHBoxLayout *hBor = new QHBoxLayout;
    QSpacerItem *s_hBor = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    hBor->addWidget(borderBar);
    hBor->addWidget(sizeBar);
    hBor->addWidget(colorBorderBar);
    hBor->addWidget(radiusBar);
    hBor->addItem(s_hBor);
    hBor->setSpacing(15);
    QHBoxLayout *hBack = new QHBoxLayout;
    hBack->setSpacing(15);
    QSpacerItem *s_Back = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    hBack->addWidget(backgroundBar);
    hBack->addWidget(colorBackgroundBar);
    hBack->addItem(s_Back);

    QVBoxLayout *barSettings = new QVBoxLayout;
    barSettings->addItem(hBor);
    barSettings->addItem(hBack);
    QWidget *bar_settings = new QWidget;
    bars.append(bar_settings);
    bar_settings->setLayout(barSettings);
    bar_settings->setStyleSheet(barStyle->GetStyleSheet());

    QHBoxLayout *results = new QHBoxLayout;
    QSpacerItem *res = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QPushButton *cansel = new QPushButton("Cancel");
    cansel->setStyleSheet(buttonStyle->GetStyleSheet());
    cansel->setFixedSize(120, 35);
    QPushButton *apply = new QPushButton("Apply changes");
    apply->setStyleSheet(buttonStyle->GetStyleSheet());
    apply->setFixedSize(120, 35);
    QPushButton *ok = new QPushButton("Ok");
    ok->setStyleSheet(buttonStyle->GetStyleSheet());
    ok->setFixedSize(120, 35);
    results->addItem(res);
    results->addWidget(cansel);
    results->addWidget(apply);
    results->addWidget(ok);
    results->setSpacing(15);

    QVBoxLayout *page = new QVBoxLayout;
    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    page->addWidget(title);
    page->addWidget(titleBar);
    page->addWidget(bar_settings);
    page->addItem(space);
    page->addItem(results);

    this->setLayout(page);
    this->setStyleSheet("QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");

    connect(this, SIGNAL(UpdateStyle(QString, QString)), Parent, SLOT(UpdateStyle(QString, QString)));
    connect(borderColorBar, SIGNAL(clicked()), this, SLOT(ClikedBarBorderColor()));
    connect(apply, SIGNAL(clicked()), this, SLOT(ApplySettings()));
    connect(sizeBar, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderSize(int)));
    connect(radiusBar, SIGNAL(valueChanged(int)), this, SLOT(ChangedBarBorderRadius(int)));
    connect(backgroundColorBar, SIGNAL(clicked()), this, SLOT(ClikedBarBackgroundColor()));
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
    emit UpdateStyle(barStyle->GetStyleSheet(), buttonStyle->GetStyleSheet());
}

void SettingsForm::ClikedBarBorderColor()
{
    QStyleSheetString str;
    str.SetStyleSheet(borderColorBar->styleSheet());
    QColorDialogWindow *color = new QColorDialogWindow(str.GetBackground());
    QColor barColor = color->GetColor();
    delete color;
    if (!barColor.isValid())
        return;
    str.SetBackground(barColor.name());
    borderColorBar->setStyleSheet(str.GetStyleSheet());

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
    str.SetStyleSheet(backgroundColorBar->styleSheet());
    str.SetBackground(barColor.name());
    backgroundColorBar->setStyleSheet(str.GetStyleSheet());
}

void SettingsForm::ChangedBarBorderSize(int size)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(QString::number(size), border[1], border[2]);
}

void SettingsForm::ChangedBarBorderRadius(int size)
{
    QList<QString> border = barStyle->GetBorder();
    barStyle->SetBorder(border[0], border[1], QString::number(size));
}
