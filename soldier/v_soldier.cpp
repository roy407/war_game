#include "v_soldier.h"

V_Soldier::V_Soldier()
{
    isPlayer = true;
    shift=50;
    status = MOVE;
    Type = V_SOLDIER;
}

QString V_Soldier::v_name[4]={"轻骑兵","重骑兵","弓手","投石车"};

void V_Soldier::SetPlayer(bool i)
{
    isPlayer = i;
}

QString V_Soldier::GetName()
{
    return name;
}

void V_Soldier::SetStatus(V_SOLDIER_STATUS i)
{
    status = i;
}

V_SOLDIER_STATUS V_Soldier::GetStatus() const
{
    return status;
}

void V_Soldier::SetSStatus(SOLDIER s)
{
    SoldierStatus = s;
}

SOLDIER V_Soldier::GetSStatus() const
{
    return SoldierStatus;
}

int V_Soldier::GetStrikingDistance() const
{
    return strikingdistance;
}

double V_Soldier::GetSpeed() const
{
    return speed;
}

double V_Soldier::GetAttackRate() const
{
    return attackRate;
}

QString V_Soldier::GetLPhotoPath() const
{
    return m_LPhotoPath;
}

QString V_Soldier::GetRPhotoPath() const
{
    return m_RPhotoPath;
}

double V_Soldier::GetHP() const
{
    return HP;
}

double V_Soldier::GetArmor() const
{
    return armor;
}

//0.1s调用一次
bool V_Soldier::Attack(V_Soldier *enemy)
{
    //每间隔一定时间攻击一下
    static int A_R = 0;
    if(A_R < attackRate){
        A_R++;
        //等待攻击期间
    }else{
        A_R = 0;
        enemy->Attacked(attack);
        return true;
    }
    return false;
}

void V_Soldier::Attacked(double Attack)
{
    //简单计算公式
    HP -= Attack;
    if(HP<=0)status = DIE;
}

double V_Soldier::GetAttack() const
{
    return attack;
}

int V_Soldier::GetPopulation() const
{
    return population;
}

void V_Soldier::AddPopulation(int i)
{
    population+=i;
}

bool V_Soldier::ReducePopulation(int i)
{
    if(population>=i){
        population-=i;
        return true;
    }else{
        return false;
    }
}

ITEM_TYPE V_Soldier::type()
{
    return Type;
}

void V_Soldier::Run()
{
    advance(1);
}

QRectF V_Soldier::boundingRect() const
{
    return QRectF(-44,-44,88,88);
}

void V_Soldier::advance(int phase)
{
    if(!phase) return;
    switch(status){
    case MOVE:
        if(isPlayer == true){
            setPos(x()+speed,y());
        }else{
            setPos(x()-speed,y());
        }
        break;
    case STOP:
        break;
    case SHIFTSTART:
        if(shift==0) status = SHIFTDOWN;
        else shift--;
        break;
    case SHIFTDOWN:
        break;
    case ATTACK:
        /*战斗代码*/
        break;
    case DIE:
        /*死亡*/
        break;
    }
}

void V_Soldier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF rect = boundingRect();
    QFont font("宋体", 10); // 设置字体
    font.setBold(true);
    QPen pen(Qt::black); // 设置画笔颜色
    painter->setFont(font);
    painter->setPen(pen);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    if(isPlayer == true){
        painter->drawPixmap(boundingRect().toRect(),QPixmap(m_LPhotoPath));
    }else{
        painter->drawPixmap(boundingRect().toRect(),QPixmap(m_RPhotoPath));
    }
    if(status==ATTACK){
        painter->drawText(rect.left(),rect.top()-5,88,18,Qt::AlignCenter,QString::number(population));
    }
}
