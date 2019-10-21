#include "qstylesheetstring.h"
#include <QDebug>

void QStyleSheetString::CreateState(QString state, QString propereties, QString value)
{
    QString new_state = name + state + QLatin1String(" {"
													 "") + propereties + ": " + value +
									   QLatin1String("; }"
													 "");
    style_sheet.append(new_state);
}

void QStyleSheetString::AddState(QString state)
{
    style_sheet.append(name + state + QLatin1String(""
                                                 ""));
}

void QStyleSheetString::CreatePropereties(int position, QString propereties, QString value)
{
    QString new_propereties = propereties + ": " + value + ";" + QLatin1String(""
                                                                                                                                                       "");
    int start = style_sheet.indexOf("{", position);
    style_sheet.insert(start + 1, new_propereties);
}

void QStyleSheetString::RenameObject(QString new_name)
{
    int size = name.size();
    int pos = style_sheet.indexOf(name);
    while (pos != -1)
    {
            style_sheet.replace(pos, size, new_name);
            pos = style_sheet.indexOf(name);
    }
    name = new_name;
}

QStyleSheetString::QStyleSheetString()
{
    name = "QWidget";
    style_sheet = name + QLatin1String(" {"
                                       "background: white;"
                                       "color: black; }"
                                       "");
}

QStyleSheetString::QStyleSheetString(QString object)
{
    name = object;
    style_sheet = name + QLatin1String(" {"
                                       "background: white;"
                                       "color: black; }"
                                       "");
}

QStyleSheetString::QStyleSheetString(const QStyleSheetString &other)
{
	style_sheet = other.style_sheet;
	name = other.name;
}

void QStyleSheetString::SetStyleSheet(QString style)
{
	style_sheet = style;
}

void QStyleSheetString::SetPropereties(QString state, QString propereties, QString value)
{
    int start = style_sheet.indexOf(name+state);
    if (start == -1)
    {
            CreateState(state, propereties, value);
            return;
    }
    int range = style_sheet.indexOf("}", start);
    int prop_loc = style_sheet.indexOf(propereties, start);
    if (prop_loc == -1 || prop_loc > range)
    {
            CreatePropereties(start, propereties, value);
            return;
    }
    int value_loc = style_sheet.indexOf(":", prop_loc) + 2;
    int value_end = style_sheet.indexOf(";", value_loc);
    style_sheet.replace(value_loc, value_end - value_loc, value);
}

void QStyleSheetString::SetPropereties(QString propereties, QString value)
{
    int p = -1;
    int f = propereties.indexOf(':');
    while (f != -1)
    {
    	p = f;
        f = propereties.indexOf(':', p + 1);
    }
    if (p == -1)
    {
            return;
    }
    QString state = propereties.left(p);
    propereties = propereties.mid(p+1);
    SetPropereties(state, propereties, value);
}

QString QStyleSheetString::GetStyleSheet()
{
	return style_sheet;
}

QString QStyleSheetString::GetPropereties(QString state, QString propereties)
{
    int start = style_sheet.indexOf(name+state);
    if (start == -1)
    {
            return "";
    }
    int range = style_sheet.indexOf("}", start);
    int prop_loc = style_sheet.indexOf(propereties, start);
    if (prop_loc == -1 || prop_loc > range)
    {
            return "";
    }
    int value_loc = style_sheet.indexOf(":", prop_loc) + 2;
    int value_end = style_sheet.indexOf(";", value_loc);
    return style_sheet.mid(value_loc, value_end - value_loc);
}

QString QStyleSheetString::GetName()
{
	return name;
}

bool QStyleSheetString::RemovePropereties(QString state, QString propereties)
{
    int start = style_sheet.indexOf(name+state);
    if (start == -1)
    {
            return false;
    }
    int range = style_sheet.indexOf("}", start);
    int prop_loc = style_sheet.indexOf(propereties, start);
    if (prop_loc == -1 || prop_loc > range)
    {
            return false;
    }
    int end_prop = style_sheet.indexOf(";", prop_loc);
    style_sheet.remove(prop_loc, end_prop - prop_loc + 1);
    return true;
}

bool QStyleSheetString::RemoveState(QString state)
{
    int start = style_sheet.indexOf(name+state);
    if (start == -1)
    {
            return false;
    }
    int end = style_sheet.indexOf("}", start);
    style_sheet.remove(start, end - start + 1);
    return true;
}

