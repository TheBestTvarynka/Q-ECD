#include "qcolordialogwindow.h"
#include <QDebug>

QColorDialogWindow::QColorDialogWindow(QColor initial)
{
    color = initial;

    red = new QSpinBox;
    red->setMinimum(0);
    red->setMaximum(255);
    red->setValue(color.red());
    green = new QSpinBox;
    green->setMinimum(0);
    green->setMaximum(255);
    green->setValue(color.green());
    blue = new QSpinBox;
    blue->setMinimum(0);
    blue->setMaximum(255);
    blue->setValue(color.blue());

    QLineEdit *name = new QLineEdit(color.name());

    QVBoxLayout *components = new QVBoxLayout;
    components->addWidget(red);
    components->addWidget(green);
    components->addWidget(blue);
    components->addWidget(name);

    example = new QPushButton;
    example->setStyleSheet("QPushButton { background: " + color.name() +"; border: none; }");

    QHBoxLayout *chooseColor = new QHBoxLayout;
    chooseColor->addItem(components);
    chooseColor->addWidget(example);


    QSpacerItem *answer_space = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QPushButton *ok = new QPushButton("OK");
    QPushButton *cancel = new QPushButton("Cancel");
    QHBoxLayout *result = new QHBoxLayout;
    result->addItem(answer_space);
    result->addWidget(cancel);
    result->addWidget(ok);

    QVBoxLayout *all = new QVBoxLayout;
    QSpacerItem *main_space = new QSpacerItem(40, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);
    all->addItem(chooseColor);
    all->addItem(main_space);
    all->addItem(result);

    this->setLayout(all);
    connect(this, SIGNAL(SetName(QString)), name, SLOT(setText(QString)));
    connect(red, SIGNAL(valueChanged(int)), this, SLOT(RedChanged(int)));
    connect(green, SIGNAL(valueChanged(int)), this, SLOT(GreenChanged(int)));
    connect(blue, SIGNAL(valueChanged(int)), this, SLOT(BlueChanged(int)));
    connect(name, SIGNAL(textEdited(QString)), this, SLOT(SetNameColor(QString)));

    connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(BreakColor()));
}

QColor QColorDialogWindow::GetColor()
{
    this->show();
    this->exec();
    return color;
}

QColorDialogWindow::~QColorDialogWindow()
{
    qDebug() << "deconstructor called";
}

void QColorDialogWindow::RedChanged(int value)
{
    color.setRed(value);
    example->setStyleSheet("QPushButton { background: " + color.name() +"; border: none; }");
    emit SetName(color.name());
}

void QColorDialogWindow::GreenChanged(int value)
{
    color.setGreen(value);
    example->setStyleSheet("QPushButton { background: " + color.name() +"; border: none; }");
    emit SetName(color.name());
}

void QColorDialogWindow::BlueChanged(int value)
{
    color.setBlue(value);
    example->setStyleSheet("QPushButton { background: " + color.name() +"; border: none; }");

    emit SetName(color.name());
}

void QColorDialogWindow::SetNameColor(QString name)
{
    if (name.length() != 7)
        return;
    color.setNamedColor(name);
    red->setValue(color.red());
    green->setValue(color.green());
    blue->setValue(color.blue());
}

void QColorDialogWindow::BreakColor()
{
    color.setNamedColor("4zzzzzevdf");
    this->close();
}
