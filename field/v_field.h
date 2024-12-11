#ifndef V_FIELD_H
#define V_FIELD_H

#include <QGraphicsItem>
#include <QGraphicsScene>

#include "communicate.h"
#include "v_building.h"
#include "soldier/v_soldier.h"
#include "soldier/v_sagittary.h"
#include "soldier/v_lightcavalry.h"
#include "soldier/v_heavycavalry.h"
#include "soldier/v_stonethrower.h"
#include "soldier/general.h"

/*封地对象*/
class V_field
{
public:
    V_field();
    void AddBuilding(BUILDING building,int x,int y);
    QList<V_Building*> GetBuildings() const;
    void AddSoldier(SOLDIER soldier,int number);
    QList<V_Soldier*>& GetSoldier();
    QList<General*>& GetGeneral();
    void SetName(QString n);
    QString GetName() const;
    void GetSceneSource(QGraphicsScene* scene);
    void SetResource(int* t,int* c,int* p,int* ts,int* cs);
    int id;
private:
    QString name;
    int* m_Treasure;
    int* m_Crop;
    int* m_Population;
    int* m_TreasureSpeed;
    int* m_CropSpeed;
    QQueue<std::pair<SOLDIER,int>>* m_Taskque;
    QList<V_Building*> m_Building;
    QGraphicsScene* m_scene;
    int m_MaxBuildingNumber;
    QList<V_Soldier*> m_Soldier;  //封地内的士兵数量，与v_player中的同步更新
    QList<General*> m_General;    //封地内的将领，对战的主体
};

#endif // V_FIELD_H
