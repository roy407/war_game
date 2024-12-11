#include "general.h"

General::General(int r)  //0-3，3为名将模式
{
    s.m_Grade = 0;
    s.m_TotalEmpiricalValue = 0;
    s.m_EmpiricalValue = 0;
    s.isBusy = false;
    m_Soldier.first=NO_SOLDIER;
    m_Soldier.second=0;
    m_Population=200;
    QFile file("I:/Desktop/1codefile/QtSubject/Empire/resource/name.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        int rline = QRandomGenerator::global()->bounded(0, 1999);
        while(rline>=0){
            file.readLine();
            rline--;
        }
        s.name = file.readLine();
    }
    switch(r)
    {
    case 0:
        s.m_GrowUp = QRandomGenerator::global()->bounded(40, 60);
        s.m_Force = QRandomGenerator::global()->bounded(40, 70);
        s.m_Intelligence = QRandomGenerator::global()->bounded(40, 70);
        s.m_Commander = QRandomGenerator::global()->bounded(40, 70);
        s.m_BreakOut = QRandomGenerator::global()->bounded(70, 80);
        break;
    case 1:
        s.m_GrowUp = QRandomGenerator::global()->bounded(60, 75);
        s.m_Force = QRandomGenerator::global()->bounded(70, 100);
        s.m_Intelligence = QRandomGenerator::global()->bounded(70, 100);
        s.m_Commander = QRandomGenerator::global()->bounded(70, 100);
        s.m_BreakOut = QRandomGenerator::global()->bounded(80, 90);
        break;
    case 2:
        s.m_GrowUp = QRandomGenerator::global()->bounded(75, 85);
        s.m_Force = QRandomGenerator::global()->bounded(100, 120);
        s.m_Intelligence = QRandomGenerator::global()->bounded(100, 120);
        s.m_Commander = QRandomGenerator::global()->bounded(100, 120);
        s.m_BreakOut = QRandomGenerator::global()->bounded(90, 96);
        break;
    case 3:
        s.m_GrowUp = QRandomGenerator::global()->bounded(85, 100);
        s.m_Force = QRandomGenerator::global()->bounded(120, 140);
        s.m_Intelligence = QRandomGenerator::global()->bounded(120, 140);
        s.m_Commander = QRandomGenerator::global()->bounded(120, 140);
        s.m_BreakOut = QRandomGenerator::global()->bounded(96, 100);
        break;
    };
    UpGrade();
}

void General::SetSoldier(V_Soldier *soldier)
{
    m_Soldier.first = soldier->GetSStatus();
    m_Soldier.second = soldier->GetPopulation();
    //随时更新
    m_Attack = soldier->GetAttack()*s.m_Grade*s.m_GrowUp/100*s.m_Force;
    m_Armor = soldier->GetArmor()*s.m_Grade*s.m_GrowUp/100*s.m_Intelligence;
    m_HP = soldier->GetHP();
}

void General::SetSoldier(std::pair<SOLDIER,int> s){
    m_Soldier = s;
}

std::pair<SOLDIER,int> General::GetSoldier() const
{
    return m_Soldier;
}

bool General::UpGrade()
{
    if(s.m_Grade==100)return false;
    s.m_EmpiricalValue = s.m_TotalEmpiricalValue - s.m_EmpiricalValue;
    s.m_Grade += 1;
    s.m_TotalEmpiricalValue = (s.m_Grade-1)*(s.m_Grade-1)*20+(s.m_Grade-1)*100+200;
    if(m_Soldier.first!=NO_SOLDIER&&m_Soldier.second!=0){
        //公式要更改
    }
    m_Population = (s.m_Grade-1)*s.m_GrowUp/100.0*s.m_Commander+200;
}

//名将系统等会再加

void General::ReadFile()
{
    enum text_state{
        t_name,
        t_property,
        t_grade,
        t_grow,
        t_attack,
        t_wise,
        t_commander,
        t_breakout
    };
    QFile file("resource/general.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);  // 使用 QTextStream 读取文本
        QString country;  //国家
        while (!in.atEnd()) {
            General_M temp;
            QString line = in.readLine();
//            while(i<line.size()){
//                if(line[0]=="#"){
//                    country=line.mid(1);
//                    break;
//                }else{
//                    if(line[i]=="（"){

//                    }
//                }
//            }
        }
        file.close();
    } else {
        //打开失败
    }
}
