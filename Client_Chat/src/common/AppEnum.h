#ifndef APPENUM_H
#define APPENUM_H

#include <QObject>

class AppEnum : public QObject
{
    Q_OBJECT
public:
    enum APP {
        HOME = 0,
        SIGNUP,
        SETTING
    }Q_ENUMS(APP);

    enum SETTING {
        USERNAME,
        CONNECT,
        BACKGROUND
    } Q_ENUMS(SETTING);

    enum DATATYPE {
        REQUEST_LOGIN,
        RESULT_LOGIN,
        REQUEST_SIGNUP,
        RESULT_SIGNUP,
        MESSAGE
    };
};

#endif // APPENUM_H
