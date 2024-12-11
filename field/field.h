#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include "v_field.h"
#include "v_building.h"
#include "v_player.h"


/*每个封地背景的显示类，还用于设置封地对象位置*/
class Field : public QGraphicsItem
{
public:
    Field(V_field* field);
protected:
    QRectF boundingRect() const override;
private:
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
private:
    V_field* m_field;
};

#endif // FIELD_H
