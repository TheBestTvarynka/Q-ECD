#include "qstylesheetstring.h"

QStyleSheetString::QStyleSheetString()
{
    styleSheet = QLatin1String("QWidget {"
                               "background: #6ac7bc;"
                               "border: 2px solid #1d7f88;"
                               "border-radius: 5px; }");
}
