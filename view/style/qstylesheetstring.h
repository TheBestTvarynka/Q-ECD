#ifndef QSTYLESHEETSTRING_H
#define QSTYLESHEETSTRING_H

#include <QString>
#include <QLatin1String>

class QStyleSheetString
{
    QString styleSheet;
public:
    QStyleSheetString();
    QString GetStyleSheet() { return styleSheet; }
};

#endif // QSTYLESHEETSTRING_H
