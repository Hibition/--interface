#include "widget.h"
#include "ui_widget.h"
#include "picture.h"

#include <QFileDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    // 点击选取文件按钮，弹出文件对话框
    connect(ui->pushButton, &QPushButton::clicked, [=](){

        // 用打开的方式打开一个文件对话框
        // 打印选中该的路径名称。参数：父对象，对话框标题，默认打开路径，过滤的文件格式
        QString path = QFileDialog::getOpenFileName(this,"open",
                                                    "C:/Users/Hibition/Pictures/picture",
                                                    "image(*.png *.jpg);;All(*.*)");

        // 调试输出选择路径
        qDebug() << path;
        // 将路径显示到 lineEdit
        ui->lineEdit->setText(path);

        QDesktopServices::openUrl(QUrl::fromLocalFile(path));

//        picture * pic = new picture(this, path);
//        pic->show();

    });

    QString testPath = "D:\\多拉\\动画\\1_已存";
    QDesktopServices::openUrl(QUrl::fromLocalFile(testPath));



}

Widget::~Widget()
{
    delete ui;
}

