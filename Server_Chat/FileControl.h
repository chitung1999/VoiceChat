#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class FileControl
{
public:
    FileControl();

    static bool readFile(QString path, QJsonObject &data);
    static bool readFile(QString path, QJsonArray &data);
    static bool writeFileJson(QString path, QJsonObject &data);
    static bool writeFileJson(QString path, QJsonArray &data);
    static bool checkFileImg(QString &path);
};

#endif // FILECONTROL_H
