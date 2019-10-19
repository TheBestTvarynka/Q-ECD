#ifndef QCHOOSENUMBERBOX_H
#define QCHOOSENUMBERBOX_H

#include <QSpinBox>

#include "qcolordialogwindow.h"
#include "../style/qstylesheetstring.h"
#include "isetter.h"

class QChooseNumberBox : public QSpinBox, public ISetter
{
    Q_OBJECT
public:
    QChooseNumberBox(QVariant);
public slots:
    void NumberEdited(int);
};

#endif // QCHOOSENUMBERBOX_H
