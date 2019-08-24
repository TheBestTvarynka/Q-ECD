#include "settingsform.h"
#include "ui_settingsform.h"
#include <QDebug>

SettingsForm::SettingsForm(QStyleSheetString *bar, QStyleSheetString *button, QWidget *parent) : QWidget(parent), ui(new Ui::SettingsForm)
{
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
    QSpacerItem *s_hBor = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    hBor->addWidget(borderBar);
    hBor->addWidget(sizeBar);
    hBor->addWidget(colorBorderBar);
    hBor->addWidget(radiusBar);
    hBor->addItem(s_hBor);
    hBor->setMargin(5);
    QHBoxLayout *hBack = new QHBoxLayout;
    hBack->setMargin(5);
    QSpacerItem *s_Back = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Preferred);
    hBack->addWidget(backgroundBar);
    hBack->addWidget(colorBackgroundBar);
    hBack->addItem(s_Back);

    QVBoxLayout *page = new QVBoxLayout;
    QSpacerItem *space = new QSpacerItem(40, 60, QSizePolicy::Preferred, QSizePolicy::Expanding);
    page->addWidget(title);
    page->addWidget(titleBar);
    page->addItem(hBor);
    page->addItem(hBack);
    page->addItem(space);

    this->setLayout(page);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
