#ifndef QSTYLESHEETSTRING_H
#define QSTYLESHEETSTRING_H

#include <QString>
#include <QLatin1String>

class QStyleSheetString
{
    QString styleSheet;
    void Border(int, QString, QString, QString);
    void Background(int, QString);
    void TextColor(int, QString);
public:
    QStyleSheetString();
    QStyleSheetString(QString);
    QString GetStyleSheet() { return styleSheet; }
    void SetBorder(QString, QString, QString);
    void SetBackground(QString);
    void SetTextColor(QString);
    void SetHoverBorder(QString, QString, QString);
    void SetHoverBackground(QString);
    void SetHoverTextColor(QString);
};

#endif // QSTYLESHEETSTRING_H
