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
    QSpinBox *sizeBar = new QSpinBox;
    sizeBar->setMinimum(0);
    sizeBar->setSingleStep(1);
//    sizeBar->setDisplayIntegerBase(curBorder[0].toInt());

    QPushButton *colorBorderBar = new QPushButton("");
    QStyleSheetString plainButton("QPushButton");
    plainButton.SetBorder("0", "#ffffff", "0");
    plainButton.SetBackground(curBorder[1]);
    plainButton.EraseBlock("QPushButton::hover");
    colorBorderBar->setStyleSheet(plainButton.GetStyleSheet());

    QSpinBox *radiusBar = new QSpinBox;
    radiusBar->setMinimum(0);
    radiusBar->setSingleStep(1);
//    radiusBar->setDisplayIntegerBase(curBorder[2].toInt());

    QLabel *backgroundBar = new QLabel("Background:");
    QPushButton *colorBackgroundBar = new QPushButton("");
    plainButton.SetBackground(bar->GetBackground());
    colorBackgroundBar->setStyleSheet(plainButton.GetStyleSheet());

    QHBoxLayout *hBor = new QHBoxLayout;
    QSpacerItem *s_hBor = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
    hBor->addWidget(borderBar);
    hBor->addWidget(sizeBar);
    hBor->addWidget(colorBorderBar);
    hBor->addWidget(radiusBar);
    hBor->addItem(s_hBor);
    hBor->setSpacing(15);
    QHBoxLayout *hBack = new QHBoxLayout;
    hBack->setSpacing(15);
    QSpacerItem *s_Back = new QSpacerItem(40, 60, QSizePolicy::Expanding, QSizePolicy::Preferred);
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
    this->setStyleSheet(".QWidget {"
                        "background-color: #d0f3f7;"
                        "color: black; }");

    connect(this, SIGNAL(UpdateStyle(QString, QString)), Parent, SLOT(UpdateStyle(QString, QString)));
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
