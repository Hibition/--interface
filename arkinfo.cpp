#include "arkinfo.h"

ArkInfo::ArkInfo()
{

}

//通过ark标志文件路径来添加ark到list
void ArkInfo::addArk(QString filename)
{
    QFile arkfile(filename);
    QString ls;
    arkfile.open(QIODeviceBase::ReadOnly);
    ls = arkfile.readAll();
    QStringList list = ls.split("\r\n");
    //将标志文件路径添加到position zero
    list.insert(0, filename);
    this->arkList.append(list);
    arkfile.close();
}

void ArkInfo::clearArk()
{
    this->arkList.clear();
}

//通过ark name从arklist中查找ark
QStringList ArkInfo::findArkByName(QString name)
{
    QStringList list;
    for(QStringList ls: this->arkList){
        if(name == ls[1]) {list = ls;}
    }
    return list;
}
