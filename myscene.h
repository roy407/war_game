#ifndef MYSCENE_H
#define MYSCENE_H

#include <QMimeData>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QTimer>

#include "fight.h"
#include "field/field.h"

enum SCENE{
    WORLD,
    FIGHT,
    FIELD
};

class MyScene : public QGraphicsScene
{
public:
    explicit MyScene(QObject *parent);
    ~MyScene();
    void WorldAFieldScene();
    void FightScene(Fight* fight);
    void SetFieldScene(V_field* field);
    SCENE GetStatus() const;
    void SetMap(Map* map);
    Map* GetMap() const;
    V_field* GetV_field() const;
    void remove();
public slots:
    void SetFightScene(Fight* fight);
    void updateFightMessage();
    void updateFightMessage(int l,int r);
private:
    Fight* fight;
    Map* map;
    Field* field;    //field的性质跟其它两个不同
    V_field* v_field;
    SCENE status;
};

#endif // MYSCENE_H
