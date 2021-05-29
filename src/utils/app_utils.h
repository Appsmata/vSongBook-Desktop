#ifndef APPUTILS_H
#define APPUTILS_H

#include <QObject>

class AppUtils
{
public:
    static QString replaceList(QString text)
    {
        text = text.replace("\\n", " ");
        text = text.replace("\\", "");
        return text;
    }

    static QString replaceView(QString text)
    {
        text = text.replace("\\n", "\r\n");
        text = text.replace("\\", "");
        return text;
    }

};

#endif // APPUTILS_H
