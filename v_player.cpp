#include "v_player.h"

V_Player::V_Player(Map* map)
{
    QTimer* timer = new QTimer(this);
    timer->start(1000);
    m_Treasure = 5000;
    m_Crop = 5000;
    m_population = 0;
    m_Treasure_Speed = 0;
    m_Crop_Speed = 0;
    m_Country = "t1";
    AllField = 10; //
    m_Map = map;
    QList<V_City*> city = m_Map->GetCity();
    SetCity(city[1]);
    SetField(city[1]->GetID());
    m_Field[0]->AddSoldier(LIGHTCAVALRY,200);
    m_Fight.push_back(new Fight(-1));
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateData()));
    Fight_Queue queue;
    queue.general = QList<General*>();
    queue.id = 10;
}

int V_Player::SoldierTime[10]={1,2,3,4,5,6,7,8,9,10};

bool V_Player::SetField(int id)
{
    if(AllField>0)AllField-=1;
    else return false;     //设置失败
    V_City* city=nullptr;
    for(int i=0;i<m_City.size();i++){
        if(m_City[i]->GetID()==id){
            city=m_City[i];
        }
    }
    if(city==nullptr)return false;
    city->s.hasfield=true;
    city->s.manor+=1;
    V_field* field = new V_field();
    field->id = city->GetID();
    field->SetName(city->s.name+"封地");
    field->SetResource(&m_Treasure,&m_Crop,&m_population,&m_Treasure_Speed,&m_Crop_Speed);
    m_Field.push_back(field);
    return true;
}

void V_Player::SetCity(V_City* city)
{
    city->s.isHave=true;
    city->s.country=m_Country;
    m_City.push_back(city);
}

void V_Player::SetFight(Fight_Queue queue)
{
    Fight* fight = nullptr;
    bool isFind = false;
    //因为技术原因，这一部分实现地并不是很好，只能现出一个简单的版本
    for(int i=0;i<m_Fight.size();i++){
        if(m_Fight[i]->GetID()==-1||m_Fight[i]->GetID()==queue.id){
            m_Fight[i]->SetID(queue.id);
            for(int j=0;j<queue.general.size();j++){
                m_Fight[i]->AddLSoldier(GenerateSoldier(queue.general[j]));
            }
            QList<General*> v=m_Map->GetSoldier(queue.id);
            for(int j=0;j<v.size();j++){
                m_Fight[i]->AddRSoldier(GenerateSoldier(v[j]));
            }
            fight = m_Fight[i];
            isFind = true;
            break;
        }
    }
    if(isFind == false){
        m_Fight.push_back(new Fight(queue.id));
        for(int j=0;j<queue.general.size();j++){
            m_Fight[m_Fight.size()-1]->AddLSoldier(GenerateSoldier(queue.general[j]));
        }
        QList<General*> v=m_Map->GetSoldier(queue.id);
        for(int j=0;j<v.size();j++){
            m_Fight[m_Fight.size()-1]->AddRSoldier(GenerateSoldier(v[j]));
        }
        fight = m_Fight[m_Fight.size()-1];
    }
    emit CreateFight(fight);
}

V_Soldier *V_Player::GenerateSoldier(General *general)
{
    //在未来，要将将军的加成加进去
    switch(general->GetSoldier().first)
    {
    case LIGHTCAVALRY:
        return new V_LightCavalry(general->GetSoldier().second);
        break;
    case HEAVYCAVALRY:
        return new V_HeavyCavalry(general->GetSoldier().second);
        break;
    case SAGITTARY:
        return new V_Sagittary(general->GetSoldier().second);
        break;
    case STONETHROWER:
        return new V_StoneThrower(general->GetSoldier().second);
        break;
    };
}

void V_Player::UpdateData()
{
    //财富、粮食产量
    m_Treasure += m_Treasure_Speed;
    m_Crop += m_Crop_Speed;
    //行军时间计算
    for(int i=0;i<m_Taskque.size();i++){
        if(m_Taskque[i]->time==0){
            SetFight(*m_Taskque[i]);
            delete m_Taskque[i];
            m_Taskque.erase(m_Taskque.begin()+i);
        }
        m_Taskque[i]->time--;
    }
    for(int i=0;i<m_Fight.size();i++){
        if(m_Fight[i]->WhoWin==1){
            for(int j=0;j<m_City.size();j++){
                if(m_City[j]->GetID()==m_Fight[i]->GetID()){
                    SetCity(m_City[j]);
                    m_Fight[i]->ClearFight();
                    break;
                }
                m_Fight[i]->WhoWin=-1;
            }
        }else if(m_Fight[i]->WhoWin==2){
            m_Fight[i]->ClearAll();
            m_Fight[i]->ClearFight();
        }
    }
}
