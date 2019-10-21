#include "qchoosenumberbox.h"
#include <QDebug>

QChooseNumberBox::QChooseNumberBox(QVariant startValue) : ISetter(startValue)
{
    this->setMinimum(0);
    this->setSingleStep(1);
    qDebug() << startValue.toString();
    this->setValue(startValue.toString().toInt());
    this->setFixedHeight(30);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(NumberEdited(int)));
}

void QChooseNumberBox::NumberEdited(int newNumber)
{
    SetValue(QVariant(QString::number(newNumber)));
}
