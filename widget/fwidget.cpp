#include "fwidget.h"

FWidget::FWidget(QWidget *parent)
    : QWidget{parent}
{
    QPushButton* button = new QPushButton("地址",this);
    button->setGeometry(0,0,100,100);
}
