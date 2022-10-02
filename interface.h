#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "Entity.h"
#include "arkinfo.h"


namespace Ui {
class Interface;
}

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

    void loadEntitys();
    void showTable();
    void showList();

    //通过‘标志文件’来添加Ark进列表
    void loadArk(QString arkPath);
    //通过‘ark_list文件初始化arklist
    void loadArkList();
    int findData(QString name);
    void openDir(QString path);
    void switchArk(QString name);
    void printArkInfo(QString name);

    void addArk();


private:
    Ui::Interface *ui;

    QVector<Entity> entitys;
    ArkInfo *arkList;
    QString path;
    //写死了，锁定Animation分类
    QString subDir = "";
};

#endif // INTERFACE_H
