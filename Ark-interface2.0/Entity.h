#ifndef ENTITY_H
#define ENTITY_H
#include <QStringList>
#include <QFileInfo>
#include <QDebug>

#include "fao.h"

class Entity{
private:
    QFileInfo fileInfo;

public:
    Entity(QFileInfo fileInfo);

    QStringList getList();
    QFileInfo getFileinfo() {return fileInfo;}


};

#endif // ENTITY_H
