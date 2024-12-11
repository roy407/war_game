#include "v_sagittary.h"

V_Sagittary::V_Sagittary(int p)
{
    m_LPhotoPath=":/resource/gs_l.png";
    m_RPhotoPath=":/resource/gs_r.png";
    name = "弓手";
    HP = 3.5;
    attack = 4;
    attackRate = 1;
    population = p;
    speed = 0.4;
    strikingdistance = 2;
    SoldierStatus = SAGITTARY;
}
