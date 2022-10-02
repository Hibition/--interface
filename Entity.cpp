#include "Entity.h"


Entity::Entity(QFileInfo fileInfo)
{
    FAO fao;
    this->fileInfo = fileInfo;

    //list.append(QString::number(fao.getDirSize(fileInfo.absoluteFilePath())));
}



QStringList Entity::getList()
{
    QStringList list;
    list.append(fileInfo.baseName());
    list.append("0");

    return list;
}
