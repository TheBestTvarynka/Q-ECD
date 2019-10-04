#ifndef QSTYLESHEETSTRING_H
#define QSTYLESHEETSTRING_H

#include <QString>
#include <QLatin1String>

class QStyleSheetString
{
	QString style_sheet;
	QString name;
public:
	QStyleSheetString(QString object);
	QStyleSheetString(const QStyleSheetString &other);
	void CreateState(QString state, QString propereties, QString value);
	void AddState(QString state);
	void CreatePropereties(int position, QString propereties, QString value);
	void RenameObject(QString new_name);
	void SetStyleSheet(QString style);
	void SetPropereties(QString state, QString propereties, QString value);
	void SetPropereties(QString propereties, QString value);
	QString GetStyleSheet();
	QString GetPropereties(QString state, QString propereties);
	bool RemovePropereties(QString state, QString propereties);
	bool RemoveState(QString state);
};

#endif // QSTYLESHEETSTRING_H
