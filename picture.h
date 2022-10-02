#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>

class picture : public QWidget
{
    Q_OBJECT
public:
    explicit picture(QWidget *parent = nullptr, QString fileName = nullptr);


signals:

};

#endif // PICTURE_H
