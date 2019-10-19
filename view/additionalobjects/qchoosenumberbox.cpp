#include "qchoosenumberbox.h"

QChooseNumberBox::QChooseNumberBox(QVariant startValue) : ISetter(startValue)
{
    this->setMinimum(0);
    this->setSingleStep(1);
    this->setValue(startValue.toInt());
    this->setFixedHeight(30);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(NumberEdited(int)));
}

void QChooseNumberBox::NumberEdited(int newNumber)
{
    SetValue(QVariant(newNumber));
}
