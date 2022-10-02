#include "clickedlabel.h"



void ClickedLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this);
}

void ClickedLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
}
