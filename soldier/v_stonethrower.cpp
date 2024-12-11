#include "v_stonethrower.h"

V_StoneThrower::V_StoneThrower(int p)
{
    m_LPhotoPath=":/resource/zz_l.png";
    m_RPhotoPath=":/resource/zz_r.png";
    name = "投石车";
    HP = 2;
    attack = 6;
    attackRate = 1;
    population = p;
    speed = 0.2;
    strikingdistance = 3;
    SoldierStatus = STONETHROWER;
}
