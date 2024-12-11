#include "v_town.h"

V_Town::V_Town()
{
    size = TOWN;
    m_PhotoPath = ":/resource/Town.png";
    s.size="小镇";
    s.country="无归属";
    s.manor=0;
    s.owner="无";
    s.talent="无";
    s.tax=0.05;
}
