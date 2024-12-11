#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QTransform>
#include<QDebug>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>


#include "myscene.h"

class MyView : public QGraphicsView
{
public:
    explicit MyView(MyScene *scene, QWidget *parent = nullptr);
private:
    void wheelEvent(QWheelEvent *event) override;
    void zoom(float scaleFactor);
    bool isMove;
    QPointF lastPoint;
    QPointF thisPoint;
    MyScene* m_Scene;
};

#endif // MYVIEW_H
