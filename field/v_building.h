#ifndef V_BUILDING_H
#define V_BUILDING_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>
#include <QLayout>
#include <QPainter>
#include <QObject>
#include <QDialog>
#include <QQueue>
#include <QLabel>
#include <QTimer>
#include <QDebug>

#include "communicate.h"
#include "soldier/v_soldier.h"
#include "soldier/general.h"

//需要将QObject放在前面！！不然会报错。
class V_Building :public QGraphicsItem
{
public:
    V_Building();
    static QList<QString> v_name;
    void SetResource(int* t,int* c,int* p,int* ts,int* cs,QList<V_Soldier*> *Soldier,QList<General*> *General);
    void SetStatus(BUILDING building);
    BUILDING GetStatus() const;
    void UpGrade();
protected:
    QRectF boundingRect() const override;
protected:
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    int* m_Treasure;
    int* m_Crop;
    int* m_Population;
    int* m_TreasureSpeed;
    int* m_CropSpeed;
    QList<V_Soldier*>* m_Soldier;
    QList<General*>* m_General;
    int m_Grade;
    bool isArmy;
    bool isBusy;           //是否在忙
    static int time[10];   //升级时间
    int timer;
    QString m_PhotoPath;
    QString name;
    BUILDING m_Building;
};

class V_NBuilding :public V_Building
{
public:
    virtual int GetData(){}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

//任务队列，在此处需要建立计时函数
class V_FBuilding :public QObject,public V_Building
{
Q_OBJECT
public:
    V_FBuilding();
    static int SoldierTime[10];
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void advance(int phase) override;
private slots:
    void updateMessage();
protected:
    //QList<V_Soldier*> s;
    //任务队列在此处不再建立，等待上层传输过来队列任务，我们直接反馈给V_Player
    QQueue<std::pair<SOLDIER,int>> que;   //任务队列，用于生产军队
};

class V_Business_Center : public V_NBuilding
{
public:
    V_Business_Center();
    int GetData() override;
private:
    int m_Speed[10];
};

class V_House : public V_NBuilding
{
public:
    V_House();
    int GetData() override;
private:
    int m_Data[10];
};

class V_Farm : public V_NBuilding
{
public:
    V_Farm();
    int GetData() override;
private:
    int m_Speed[10];
};

class V_Infantry_Training_Center : public V_FBuilding
{
public:
    V_Infantry_Training_Center();
private:

};

class V_Cavalry_Training_Center : public V_FBuilding
{
public:
    V_Cavalry_Training_Center();
};

class V_Tank_Manufacturing_Center : public V_FBuilding
{
public:
    V_Tank_Manufacturing_Center();
};

class V_Tavern : public V_FBuilding
{
public:
    V_Tavern();
};

#endif // V_BUILDING_H
