#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QString>

enum V_CITY_SIZE{
    CAPITAL,
    PROVINCIAL_CAPITAL,
    COUNTYTOWN,
    TOWN
};

struct City_M{
    QString name;
    QString size;
    QString country;
    QString owner;
    QString talent;
    int manor;
    double tax;
    bool hasfield;
    bool isHave;
};

enum V_SOLDIER_STATUS{
    DIE,
    STOP,
    MOVE,
    ATTACK,
    SHIFTSTART,
    SHIFTDOWN
};

enum BUILDING{
    BUSINESS_CENTER,
    HOUSE,
    FARM,
    INFANTRY_TRAINING_CENTER,
    CAVALRY_TRAINING_CENTER,
    TANK_MANUFACTURING_CENTER,
    TAVERN
};

enum ITEM_TYPE{
    V_CITY,
    V_SOLDIER
};

enum MESSAGE_STATUS{
    V_CITY_MESSAGE,
    HASBUILT_MESSAGE,
    GENERAL_MESSAGE,
    SOLDIER_MESSAGE,
    BUILD_MESSAGE,
    ATTACK_MESSAGE,
    NO_MESSAGE
};

enum SOLDIER{
    NO_SOLDIER,
    LIGHTCAVALRY,
    HEAVYCAVALRY,
    SAGITTARY,
    STONETHROWER
};

struct General_M{
    QString name;        //将领名字
    int m_Grade;         //将领等级                       1-100
    int m_Force;         //与攻击力相关
    int m_Intelligence;  //与护甲相关
    int m_Commander;     //与统帅人数有关
    int m_BreakOut;      //突围值与逃跑有关                 0-99
    int m_GrowUp;        //成长值越高，所有的数值都提升的很高  0-99
    int m_TotalEmpiricalValue;//本等级经验值
    int m_EmpiricalValue;//本等级已经有的经验值
    bool isBusy;
};
/*一次失败的尝试，为什么这种方法不行？*/
//class ALL20{
//public:
//    static Message showmessage;
//};
/*注意，一定要有初始化！！！*/
/*否则会报未定义的错误*/
//Message ALL20::showmessage={};
#endif // COMMUNICATE_H
