#ifndef V_V_SOLDIER_H
#define V_V_SOLDIER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "communicate.h"

class V_Soldier : public QGraphicsItem
{
public:
    V_Soldier();
    void SetPlayer(bool i);
    QString GetName();
    void SetStatus(V_SOLDIER_STATUS i);
    V_SOLDIER_STATUS GetStatus() const;
    void SetSStatus(SOLDIER s);
    SOLDIER GetSStatus() const;
    int GetStrikingDistance() const;
    double GetSpeed() const;
    double GetAttackRate() const;
    QString GetLPhotoPath() const;
    QString GetRPhotoPath() const;
    double GetHP() const;
    double GetArmor() const;
    bool Attack(V_Soldier* enemy);
    void Attacked(double Attack);
    double GetAttack() const;
    int GetPopulation() const;
    void AddPopulation(int i);
    bool ReducePopulation(int i);
    static QString v_name[4];
    ITEM_TYPE type();
    void Run();
protected:
    QRectF boundingRect() const override;
private:
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    QString m_LPhotoPath;
    QString m_RPhotoPath;
    int shift;
    ITEM_TYPE Type;
protected:
    //军队的基本量
    QString name;
    int strikingdistance;
    double speed;
    double attackRate;
    double HP;
    double armor;
    double attack;
    int population;
    bool isPlayer;
    V_SOLDIER_STATUS status;
    SOLDIER SoldierStatus;
};

#endif // V_V_SOLDIER_H
