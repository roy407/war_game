#ifndef FIGHT_H
#define FIGHT_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QObject>

#include "soldier/general.h"
#include "soldier/v_soldier.h"
#include "soldier/v_lightcavalry.h"
#include "soldier/v_heavycavalry.h"
#include "soldier/v_sagittary.h"
#include "soldier/v_stonethrower.h"

class Fight : public QObject
{
Q_OBJECT
public:
    explicit Fight(int id,QObject *parent = nullptr);
    ~Fight();
    void init();
    QGraphicsLineItem* GetCenterLine() const;
    QList<QGraphicsPixmapItem*> GetFightCenter() const;
    void AddLSoldier(QList<V_Soldier*> l);
    void AddLSoldier(V_Soldier* l);
    void AddRSoldier(QList<V_Soldier*> r);
    void AddRSoldier(V_Soldier* r);
    V_Soldier* AttackLBody();
    V_Soldier* AttackRBody();
    QList<V_Soldier*>& GetLSoldier();
    QList<V_Soldier*>& GetRSoldier();
    void ClearFight();
    void SetID(int id);
    int GetID();
    void ClearAll();
    int WhoWin;         //0说明还在打，1说明玩家赢，2说明电脑赢
private slots:
    void onTimeOut();
private:
    //地图资源
    QGraphicsLineItem* m_CenterLine;
    QList<QGraphicsPixmapItem*> m_FightCenter;
    QPoint pos[3][6];
    V_Soldier* lpos[3][6];
    V_Soldier* rpos[3][6];
    int stopLine=500;
    //军队资源
    QList<V_Soldier*> m_LSoldier;
    QList<V_Soldier*> m_RSoldier;
    int id;             //每场战斗的唯一标识，当id为-1时，证明这个是空战场
};

#endif // FIGHT_H
