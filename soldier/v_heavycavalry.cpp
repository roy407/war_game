#include "v_heavycavalry.h"

V_HeavyCavalry::V_HeavyCavalry(int p)
{
    m_LPhotoPath=":/resource/zq_l.png";
    m_RPhotoPath=":/resource/zq_r.png";
    name = "重骑兵";
    HP = 8;
    attack = 3;
    attackRate = 1;
    population = p;
    speed = 0.6;
    strikingdistance = 1;
    SoldierStatus = HEAVYCAVALRY;
}
