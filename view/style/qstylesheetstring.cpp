#include "qstylesheetstring.h"
#include <QDebug>

void QStyleSheetString::Border(int gPos, QString size, QString color, QString radius)
{
    int posS = styleSheet.indexOf("border", gPos);
    int posE = styleSheet.indexOf("px", posS);
    if (posS == -1 || posE == -1)
        return;
    styleSheet = styleSheet.replace(posS + 8, posE - posS - 8, size);

    posE = styleSheet.indexOf("#", posS);
    if (posE == -1)
        return;
    styleSheet = styleSheet.replace(posE, 7, color);

    posS = styleSheet.indexOf("border-radius", gPos);
    posE = styleSheet.indexOf("px", posS);
    if (posS == -1 || posE == -1)
        return;
    styleSheet = styleSheet.replace(posS + 15, posE - posS - 15, radius);
}

void QStyleSheetString::Background(int gPos, QString color)
{
    int pos = styleSheet.indexOf("background", gPos);
    if (pos == -1)
        return;
    styleSheet = styleSheet.replace(pos + 12, 7, color);
}

void QStyleSheetString::TextColor(int gPos, QString color)
{
    int pos = styleSheet.indexOf("color", gPos);
    if (pos == -1)
        return;
    styleSheet = styleSheet.replace(pos + 7, 7, color);
}

QStyleSheetString::QStyleSheetString()
{
    styleSheet = QLatin1String("QWidget {"
                               "background: #6ac7bc;"
                               "border: 2px solid #1d7f88;"
                               "border-radius: 5px;"
                               "color: #ffffff; }"
                               "QPushButton::hover {"
                               "background-color: #f24bef;"
                               "color: #585957; }");
}

QStyleSheetString::QStyleSheetString(QString name)
{
    styleSheet = "." + name + QLatin1String(" {"
                              "background: #6ac7bc;"
                              "border: 2px solid #1d7f88;"
                              "border-radius: 5px;"
                              "color: #ffffff; }"
                              ".") + name + "::hover {"
                              "background: #6ac7bc;"
                              "border: 2px solid #1d7f88;"
                              "border-radius: 5px;"
                              "color: #ffffff; }";
}

void QStyleSheetString::SetBorder(QString size, QString color, QString radius)
{
    Border(0, size, color, radius);
}

void QStyleSheetString::SetBackground(QString color)
{
    Background(0, color);
}

void QStyleSheetString::SetTextColor(QString color)
{
    TextColor(0, color);
}

void QStyleSheetString::SetHoverBorder(QString size, QString color, QString radius)
{
    int globalPos = styleSheet.indexOf("hover");
    Border(globalPos, size, color, radius);
}

void QStyleSheetString::SetHoverBackground(QString color)
{
    int globalPos = styleSheet.indexOf("hover");
    Background(globalPos, color);
}

void QStyleSheetString::SetHoverTextColor(QString color)
{
    int globalPos = styleSheet.indexOf("hover");
    TextColor(globalPos, color);
}

void QStyleSheetString::EraseBlock(QString block)
{
    int posS = styleSheet.indexOf(block);
    int posE = styleSheet.indexOf("}", posS);
    if (posS == -1 || posE == -1)
        return;
    qDebug() << styleSheet;
    styleSheet = styleSheet.remove(posS - 1, posE - posS + 2);
    qDebug() << styleSheet;
}
