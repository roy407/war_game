#ifndef V_PLAYER_H
#define V_PLAYER_H

#include <QDebug>
#include <QHash>
#include <QObject>
#include <QTimer>

#include "soldier/v_soldier.h"
#include "soldier/v_sagittary.h"
#include "soldier/v_lightcavalry.h"
#include "soldier/v_heavycavalry.h"
#include "soldier/v_stonethrower.h"
#include "city/v_city.h"
#include "field/v_field.h"
#include "map.h"
#include "fight.h"
#include "field/v_field.h"

struct Fight_Queue{
    QList<General*> general;
    int id;
    int time;
};
//注意，与外界通信一定要加上public
class V_Player : public QObject
{
Q_OBJECT
public:
    V_Player(Map* map);
public:
    int m_Treasure;                //财富值（）
    int m_Crop;                    //粮食总量
    int m_population;              //总人口
    int m_Treasure_Speed;          //财富产量
    int m_Crop_Speed;              //粮食产量
    static int SoldierTime[10];
    QString m_Country;               //所属国家
    QList<V_Soldier*> m_Soldier;   //拥有的士兵
    QList<V_City*> m_City;         //拥有的城池
    QList<V_field*> m_Field;       //封地
    QList<Fight*> m_Fight;         //战斗场景
    int AllField;
    QList<Fight_Queue*> m_Taskque; //军队行进队列
    bool SetField(int id);
    void SetCity(V_City* city);
    void SetFight(Fight_Queue queue);
    V_Soldier* GenerateSoldier(General* general);
signals:
    void CreateFight(Fight* fight);
    void AddFight(int l,int r);
private slots:
    void UpdateData();
public:
    Map* m_Map;
};

#endif // V_PLAYER_H
