#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>


class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent=nullptr) : QLabel(parent){}
    ~ClickedLabel() {}

    void mouseDoubleClickEvent(QMouseEvent* event);

signals:
    void clicked(ClickedLabel* label);
    void doubleClicked();

protected:
    void mouseReleaseEvent(QMouseEvent*);

};

#endif // CLICKEDLABEL_H
