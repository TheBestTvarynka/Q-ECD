#include "qchoosecolorbutton.h"
#include <QDebug>

QChooseColorButton::QChooseColorButton(QVariant startValue) : ISetter(startValue)
{
    style.SetStyleSheet(QLatin1String("QPushButton {"
                                      "border: 2px solid white; }"));
    style.SetPropereties("", "background", GetValue().toString());
    this->setStyleSheet(style.GetStyleSheet());
    this->setFixedHeight(30);
    connect(this, SIGNAL(clicked()), this, SLOT(ChooseColor()));
}

void QChooseColorButton::ChooseColor()
{
    QColorDialogWindow *colorSelector = new QColorDialogWindow(GetValue().toString());
    QColor newColor = colorSelector->GetColor();
    delete colorSelector;
    if (newColor.isValid())
    {
        SetValue(QVariant(newColor.name()));
        style.SetPropereties("", "background", newColor.name());
        this->setStyleSheet(style.GetStyleSheet());
    }
}
