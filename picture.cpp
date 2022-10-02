#include "picture.h"
#include "clickedlabel.h"

picture::picture(QWidget *parent, QString fileName)
    : QWidget{parent}
{
    QPixmap pix(fileName);
    ClickedLabel* label = new ClickedLabel();

    int i = 165;
    label->resize(i, i*38/27);
    label->setScaledContents(true);
    qDebug() << label->size();
    QPixmap dest=pix.scaled(QSize(270,380), Qt::KeepAspectRatioByExpanding);
    label->setPixmap(dest);
    label->show();

    connect(label, &ClickedLabel::clicked ,[=](ClickedLabel* label){qDebug() << label->size();});
    connect(label, &ClickedLabel::doubleClicked, [=](){qDebug() << "double clicked";});
}
