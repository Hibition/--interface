#include "widget.h"
#include "interface.h"
#include "fao.h"

#include <QApplication>
#include <QByteArray>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface w;
    w.show();


//    QFile file("./ark_list.txt");
//    qDebug() << file.exists();
//    qDebug() << file.open(QIODeviceBase::ReadOnly);
//    QByteArray array = file.readAll();
//    QString path =  QString(array);
//    QFile file2(path);
//    file2.open(QIODeviceBase::ReadOnly);
//    qDebug() << QString(file2.readAll()).split("\r\n");


    return a.exec();
}
