#ifndef MAP_H
#define MAP_H

#include <QRandomGenerator>
#include <QTextStream>
#include <QQueue>
#include <QFile>
#include <QDir>

#include"city/v_city.h"
#include"city/v_capital.h"
#include"city/v_provincial_capital.h"
#include"city/v_countytown.h"
#include"city/v_town.h"
#include"soldier/general.h"

class Map
{
public:
    Map();
    void init();
    void initRoad();  //绘制道路
    QList<V_City*> GetCity();
    QGraphicsPathItem* GetRoad();
    QHash<int,std::pair<std::pair<int,int>,QHash<int,bool>>> GetARoad() const;
    QList<General*> GetSoldier(int id);
    double GetPath(int start,int end);    //计算两个城市之间是否可到达,不可到达即返回0，否则返回时间
    QRect GetSize();
    ~Map();
private:
    //道路
    QGraphicsPathItem *pathItem;
    //    id                        pos          id  是否连接
    QHash<int,std::pair<std::pair<int,int>,QHash<int,bool>>> m_Road;
    //地图总大小
    int m_MaxHeight;
    int m_MaxWidth;
    //地图中心点
    std::pair<int,int> m_Center;
    QList<V_City*> m_City;
    QList<QString> v_name;
    //既然守城将领无法添加进去，那么直接写在这个地方吧
};

#endif // MAP_H
