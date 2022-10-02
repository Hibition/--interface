#ifndef ARKINFO_H
#define ARKINFO_H

#include <QList>
#include <QFile>

class ArkInfo
{
public:
    ArkInfo();

    void addArk(QString filename);
    void clearArk();

    QStringList findArkByName(QString name);

    QList<QStringList> getInfo() {return arkList;}
private:
    //这里用QStringList好像更好
    QList<QStringList> arkList;
};

#endif // ARKINFO_H
