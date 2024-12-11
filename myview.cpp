#include "myview.h"

MyView::MyView(MyScene *scene, QWidget *parent)
    : QGraphicsView(scene,parent)
{
    m_Scene = scene;
    isMove = false;
}

void MyView::wheelEvent(QWheelEvent *event)
{
    if(m_Scene->GetStatus()==WORLD){
        if(event->delta()>0){
            zoom(1+0.1);
        }else if(event->delta()<0){
            zoom(1-0.1);
        }
    }
}

void MyView::zoom(float scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if(factor<=0.1||factor>=1.1){
        return;
    }
    scale(scaleFactor, scaleFactor);
}

