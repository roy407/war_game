#include "v_field.h"

V_field::V_field()
{
    m_Treasure = nullptr;
    m_Crop = nullptr;
    m_Population = nullptr;
    m_MaxBuildingNumber=12;
    m_Soldier.push_back(new V_LightCavalry(0));
    m_Soldier.push_back(new V_HeavyCavalry(0));
    m_Soldier.push_back(new V_Sagittary(0));
    m_Soldier.push_back(new V_StoneThrower(0));
}

void V_field::AddBuilding(BUILDING building,int x,int y)
{
    for(int i=0;i<m_Building.size();i++){
        if(m_Building[i]->pos().toPoint()==QPoint(x,y)){
            return;
        }
    }
    if(m_Building.size()>m_MaxBuildingNumber) return;
    V_Building* t_building;
    switch(building)
    {
    case BUSINESS_CENTER:
        t_building=new V_Business_Center;
        break;
    case HOUSE:
        t_building=new V_House;
        break;
    case FARM:
        t_building=new V_Farm;
        break;
    case INFANTRY_TRAINING_CENTER:
        t_building=new V_Infantry_Training_Center;
        break;
    case CAVALRY_TRAINING_CENTER:
        t_building=new V_Cavalry_Training_Center;
        break;
    case TANK_MANUFACTURING_CENTER:
        t_building=new V_Tank_Manufacturing_Center;
        break;
    case TAVERN:
        t_building=new V_Tavern;
        break;
    };
    t_building->setPos(x,y);
    t_building->SetStatus(building);
    t_building->SetResource(m_Treasure,m_Crop,m_Population,m_TreasureSpeed,m_CropSpeed,&m_Soldier,&m_General);
    m_Building.push_back(t_building);
    m_scene->addItem(t_building);
}

QList<V_Building *> V_field::GetBuildings() const
{
    return m_Building;
}

void V_field::AddSoldier(SOLDIER soldier, int number)
{
    for(int i=0;i<m_Soldier.size();i++){
        if(m_Soldier[i]->GetSStatus()==soldier){
            m_Soldier[i]->AddPopulation(number);
        }
    }
}

QList<V_Soldier *> &V_field::GetSoldier()
{
    return m_Soldier;
}

QList<General *> &V_field::GetGeneral()
{
    return m_General;
}

void V_field::SetName(QString n)
{
    name = n;
}

QString V_field::GetName() const
{
    return name;
}

void V_field::GetSceneSource(QGraphicsScene *scene)
{
    m_scene = scene;
}

void V_field::SetResource(int *t, int *c, int *p,int *ts,int *cs)
{
    m_Treasure = t;
    m_Crop = c;
    m_Population = p;
    m_TreasureSpeed = ts;
    m_CropSpeed = cs;
}
