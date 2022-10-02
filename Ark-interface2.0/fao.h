#ifndef FAO_H
#define FAO_H

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>

class FAO
{
public:
    FAO();

    QFileInfoList listDir(QString path);

    void openDir(QString path);
    void openDir(QString fatherPath, QString sonPath);

    quint64 getDirSize(QString path);
};

#endif // FAO_H
