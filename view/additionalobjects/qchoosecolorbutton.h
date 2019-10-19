#ifndef QCHOOSECOLORBUTTON_H
#define QCHOOSECOLORBUTTON_H

#include <QPushButton>
#include <QColor>

#include "qcolordialogwindow.h"
#include "../style/qstylesheetstring.h"
#include "isetter.h"

class QChooseColorButton : public QPushButton, public ISetter
{
    Q_OBJECT
    QStyleSheetString style;
public:
    QChooseColorButton(QVariant);
public slots:
    void ChooseColor();
};

#endif // QCHOOSECOLORBUTTON_H
