#ifndef ISETTER_H
#define ISETTER_H

#include <QVariant>

class ISetter
{
    QVariant value;
public:
    ISetter(QVariant);
    void SetValue(QVariant newValue) { value = newValue; }
    QVariant GetValue() { return value; }
};

#endif // ISETTER_H
