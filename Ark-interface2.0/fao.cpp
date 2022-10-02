#include "fao.h"


FAO::FAO()
{

}
//通过文件夹路径找出有哪些子文件
QFileInfoList FAO::listDir(QString path)
{

    QDir *dir = new QDir(path);
    QFileInfoList files = dir->entryInfoList();

    return files;
}
//用资源管理器打开相应文件
void FAO::openDir(QString path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
//父路径与子路径版重载
void FAO::openDir(QString sonPath, QString fatherPath)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fatherPath + "\\" + sonPath));
}

quint64 FAO::getDirSize(QString path)
{
    QDir dir(path);
    quint64 size = 0;
    //统计目录下所有文件大小
    for(QFileInfo fileInfo: dir.entryInfoList(QDir::Files)){
        size += fileInfo.size();
    }
    //统计子目录大小
    for(QString subDir: dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        size += getDirSize(path + QDir::separator() + subDir);
    }
    return size;
}
