#include "v_lightcavalry.h"

V_LightCavalry::V_LightCavalry(int p)
{
    m_LPhotoPath=":/resource/qq_l.png";
    m_RPhotoPath=":/resource/qq_r.png";
    name = "轻骑兵";
    HP = 5;
    attack = 2;
    attackRate = 1;
    population = p;
    speed = 0.8;
    strikingdistance = 1;
    SoldierStatus = LIGHTCAVALRY;
}
