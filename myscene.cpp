#include "myscene.h"

MyScene::MyScene(QObject *parent)
    : QGraphicsScene{parent}
{
}

MyScene::~MyScene()
{

}

void MyScene::WorldAFieldScene()
{
    status=WORLD;
    remove();
    setSceneRect(map->GetSize());
    QGraphicsPathItem* road = map->GetRoad();
    addItem(road);
    QList<V_City*> city = map->GetCity();
    for(int i=0;i<city.size();i++){
        addItem(city[i]);
    }
    setBackgroundBrush(QPixmap(":/resource/grass.jpg"));
}

void MyScene::FightScene(Fight* fight)
{
    status=FIGHT;
    this->fight = fight;
    remove();
    fight->init();
    setSceneRect(-1000,-200,2000,400);
    QGraphicsPathItem* CenterLine = new QGraphicsPathItem;
    addItem(CenterLine);
    QList<QGraphicsPixmapItem*> FightCenter = fight->GetFightCenter();
    for(int i=0;i<FightCenter.size();i++){
        addItem(FightCenter[i]);
    }
    updateFightMessage();
    setBackgroundBrush(QPixmap(":/resource/fight.jpg"));
}

void MyScene::SetFieldScene(V_field* field)
{
    status=FIELD;
    remove();
    this->v_field = field;
    //背景类载入
    this->field = new Field(field);
    addItem(this->field);
    //建筑物载入
    QList<V_Building*> v = v_field->GetBuildings();
    for(int i=0;i<v.size();i++){
        addItem(v[i]);
    }
}

SCENE MyScene::GetStatus() const
{
    return status;
}

void MyScene::SetMap(Map *map)
{
    this->map=map;
}

Map *MyScene::GetMap() const
{
    return map;
}

V_field *MyScene::GetV_field() const
{
    return v_field;
}

void MyScene::remove()
{
    QList<QGraphicsItem*> it = items();
    for(int i=0;i<it.size();i++){
        removeItem(it[i]);
    }
}

void MyScene::SetFightScene(Fight *fight)
{
    FightScene(fight);
}

void MyScene::updateFightMessage()
{
    //战斗开始时立即加入战斗
    QList<V_Soldier*> LSoldier = fight->GetLSoldier();
    for(int i=0;i<LSoldier.size();i++){
        int randomValue = QRandomGenerator::global()->bounded(-200, 201);
        LSoldier[i]->setPos(-1000,randomValue);
        addItem(LSoldier[i]);
    }
    QList<V_Soldier*> RSoldier = fight->GetRSoldier();
    for(int i=0;i<RSoldier.size();i++){
        int randomValue = QRandomGenerator::global()->bounded(-200, 201);
        RSoldier[i]->setPos(1000,randomValue);
        addItem(RSoldier[i]);
    }
}

void MyScene::updateFightMessage(int l, int r)
{
    //战斗时中途加入战斗
    QList<V_Soldier*> LSoldier = fight->GetLSoldier();
    for(int i=l;i<LSoldier.size();i++){
        int randomValue = QRandomGenerator::global()->bounded(-200, 201);
        LSoldier[i]->setPos(-1000,randomValue);
        addItem(LSoldier[i]);
    }
    QList<V_Soldier*> RSoldier = fight->GetRSoldier();
    for(int i=r;i<RSoldier.size();i++){
        int randomValue = QRandomGenerator::global()->bounded(-200, 201);
        RSoldier[i]->setPos(1000,randomValue);
        addItem(RSoldier[i]);
    }
}
