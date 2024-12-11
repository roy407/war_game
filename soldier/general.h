#ifndef GENERAL_H
#define GENERAL_H

#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

#include "v_soldier.h"

//到目前这个地方，我只能自己瞎编公式了

class General
{
public:
    General(int r);
    void SetSoldier(V_Soldier* soldier);
    void SetSoldier(std::pair<SOLDIER,int> s);
    std::pair<SOLDIER,int> GetSoldier() const;
    bool UpGrade();
    static void ReadFile();
    static QHash<QString,QList<General_M>> m_AllG;
//写函数太累了，干脆直接全变成可以随意访问的量
public:
    std::pair<SOLDIER,int> m_Soldier;//率领的队伍多少，人数一定要小于等于实际统治人数
    General_M s;
//战斗时的实际值
    double m_Attack;
    double m_HP;
    double m_Armor;
    int m_Population;
};

#endif // GENERAL_H
