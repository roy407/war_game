#ifndef V_V_CITY_H
#define V_V_CITY_H

#include<QObject>
#include<QGraphicsItem>
#include<QPainter>
#include<QTimer>
#include<QGraphicsSceneMouseEvent>
#include<QDebug>

#include "communicate.h"
#include "field/v_field.h"

class V_City:public QGraphicsItem
{
public:
    V_City();
    ~V_City();
    std::pair<int,int> GetPos() const;
    void SetPos(std::pair<int,int> pos);
    City_M GetCityMessage() const;
    V_CITY_SIZE City_Size();
    ITEM_TYPE type();
    void SetID(int id);
    int GetID() const;
    bool isClicked;
    City_M s;
protected:
    QRectF boundingRect() const override;
private:
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
protected:
    //想不明白，为什么多加入一个成员变量后，鼠标点击事件变得这么不灵敏
    //守城将领
    //QList<General*> m_General;
    std::pair<int,int> m_Pos;
    V_CITY_SIZE size;
    QString m_PhotoPath;
    int id; //每个城市都有一个独特的id
    ITEM_TYPE Type;
};

#endif // V_V_CITY_H
