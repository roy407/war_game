#include "fight.h"

Fight::Fight(int id,QObject *parent)
    : QObject(parent)
{
    QTimer* timer = new QTimer(this);
    timer->start(100);  //战斗
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            pos[i][j]=QPoint(i*130+90,j*80-160);
            lpos[i][j]=nullptr;
            rpos[i][j]=nullptr;
        }
    }
    WhoWin = 0;
    this->id = id;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
}

Fight::~Fight()
{
    for(int i=0;i<m_LSoldier.size();i++)
        delete m_LSoldier[i];
    for(int i=0;i<m_RSoldier.size();i++)
        delete m_RSoldier[i];
    for(int i=0;i<m_FightCenter.size();i++)
        delete m_FightCenter[i];
    delete m_CenterLine;
}

void Fight::init()
{
    /*战场资源初始化*/
    QPen pen(Qt::red); // 使用红色笔
    pen.setWidth(3);   // 设置宽度为3个像素
    m_CenterLine = new QGraphicsLineItem(0,-250,0,250);
    m_CenterLine->setPen(pen);
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            QGraphicsPixmapItem* pos_l = new QGraphicsPixmapItem(QPixmap(":/resource/pos_l.png"));
            QGraphicsPixmapItem* pos_r = new QGraphicsPixmapItem(QPixmap(":/resource/pos_r.png"));
            pos_r->setPos(pos[i][j].x()-60,pos[i][j].y()-30);
            pos_l->setPos(-pos[i][j].x()-60,pos[i][j].y()-30);
            m_FightCenter.push_back(pos_l);
            m_FightCenter.push_back(pos_r);
        }
    }
    /*士兵资源初始化*/
}

QGraphicsLineItem *Fight::GetCenterLine() const
{
    return m_CenterLine;
}

QList<QGraphicsPixmapItem *> Fight::GetFightCenter() const
{
    return m_FightCenter;
}

void Fight::AddLSoldier(QList<V_Soldier *> l)
{
    for(int i=0;i<l.size();i++){
        m_LSoldier.push_back(l[i]);
    }
}

void Fight::AddLSoldier(V_Soldier *l)
{
    m_LSoldier.push_back(l);
}

void Fight::AddRSoldier(QList<V_Soldier *> r)
{
    for(int i=0;i<r.size();i++){
        m_RSoldier.push_back(r[i]);
        r[i]->SetPlayer(false);
    }
}

void Fight::AddRSoldier(V_Soldier *r)
{
    m_RSoldier.push_back(r);
    r->SetPlayer(false);
}

V_Soldier *Fight::AttackLBody()
{
    for(int i=0;i<5;i++){
        if(lpos[0][i]==nullptr){
            if(lpos[1][i]==nullptr){
                if(lpos[2][i]!=nullptr){
                    return lpos[2][i];
                }
            }else{
                return lpos[1][i];
            }
        }
    }
    for(int i=0;i<5;i++){
        if(lpos[0][i]!=nullptr){
            return lpos[0][i];
        }
    }
}

V_Soldier *Fight::AttackRBody()
{
    for(int i=0;i<5;i++){
        if(rpos[0][i]==nullptr){
            if(rpos[1][i]==nullptr){
                if(rpos[2][i]!=nullptr){
                    return rpos[2][i];
                }
            }else{
                return rpos[1][i];
            }
        }
    }
    for(int i=0;i<5;i++){
        if(rpos[0][i]!=nullptr){
            return rpos[0][i];
        }
    }
}

QList<V_Soldier *> &Fight::GetLSoldier()
{
    return m_LSoldier;
}

QList<V_Soldier *> &Fight::GetRSoldier()
{
    return m_RSoldier;
}

void Fight::ClearFight()
{
    /*判断死亡*/
    for(int i=0;i<m_LSoldier.size();i++){
        if(m_LSoldier[i]->GetStatus()==DIE){
            for(int j=0;j<5;j++){
                for(int k=0;k<3;k++){
                    if(m_LSoldier[i]==lpos[k][j]){
                        delete lpos[k][j];
                        lpos[k][j]=nullptr;
                    }
                }
            }
        }
    }
    for(int i=0;i<m_RSoldier.size();i++){
        if(m_RSoldier[i]->GetStatus()==DIE){
            for(int j=0;j<5;j++){
                for(int k=0;k<3;k++){
                    if(m_RSoldier[i]==rpos[k][j]){
                        delete rpos[k][j];
                        rpos[k][j]=nullptr;
                    }
                }
            }
        }
    }
}

void Fight::SetID(int id)
{
    this->id = id;
}

int Fight::GetID()
{
    return id;
}

void Fight::ClearAll()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            pos[i][j]=QPoint(i*130+90,j*80-160);
            lpos[i][j]=nullptr;
            rpos[i][j]=nullptr;
        }
    }
    WhoWin = 0;
    id = -1;
    m_LSoldier.clear();
    m_RSoldier.clear();
}

//此处代码还需要大改，暂时先搞成这样
void Fight::onTimeOut()
{
    if(WhoWin==0&&id!=-1){
        /*进入对战前准备*/
        for(int i=0;i<m_LSoldier.size();i++){
            if(m_LSoldier[i]->pos().x()>=-stopLine&&m_LSoldier[i]->GetStatus()==MOVE){
                m_LSoldier[i]->SetStatus(SHIFTSTART);
            }
        }
        for(int i=0;i<m_RSoldier.size();i++){
            if(m_RSoldier[i]->pos().x()<=stopLine&&m_RSoldier[i]->GetStatus()==MOVE){
                m_RSoldier[i]->SetStatus(SHIFTSTART);
            }
        }
        /*对战准备，各部门入坐*/
        for(int i=0;i<m_LSoldier.size();i++){
            if(m_LSoldier[i]->pos().x()>=-stopLine&&m_LSoldier[i]->GetStatus()==SHIFTDOWN){
                for(int j=0;j<5;j++){
                    if(lpos[m_LSoldier[i]->GetStrikingDistance()-1][j]==nullptr){
                        lpos[m_LSoldier[i]->GetStrikingDistance()-1][j]=m_LSoldier[i];
                        m_LSoldier[i]->SetStatus(ATTACK);
                        QPointF temp=pos[m_LSoldier[i]->GetStrikingDistance()-1][j];
                        m_LSoldier[i]->setPos(-temp.x(),temp.y());
                        break;
                    }
                }
            }
        }
        for(int i=0;i<m_RSoldier.size();i++){
            if(m_RSoldier[i]->pos().x()<=stopLine&&m_RSoldier[i]->GetStatus()==SHIFTDOWN){
                for(int j=0;j<5;j++){
                    if(rpos[m_RSoldier[i]->GetStrikingDistance()-1][j]==nullptr){
                        rpos[m_RSoldier[i]->GetStrikingDistance()-1][j]=m_RSoldier[i];
                        m_RSoldier[i]->SetStatus(ATTACK);
                        m_RSoldier[i]->setPos(pos[m_RSoldier[i]->GetStrikingDistance()-1][j]);
                        break;
                    }
                }
            }
        }
        /*对战*/
        for(int i=0;i<m_LSoldier.size();i++){
            if(m_LSoldier[i]->GetStatus()==ATTACK){
                m_LSoldier[i]->Attack(AttackRBody());
            }
        }
        for(int i=0;i<m_RSoldier.size();i++){
            if(m_RSoldier[i]->GetStatus()==ATTACK){
                m_RSoldier[i]->Attack(AttackLBody());
            }
        }
        /*判断输赢*/
        bool isFindL=false;
        for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                if(lpos[j][i]!=nullptr&&lpos[j][i]->GetStatus()!=DIE){
                    isFindL=true;
                }
            }
        }
        for(int i=0;i<m_LSoldier.size();i++){
            if(m_LSoldier[i]->GetStatus()!=DIE){
                isFindL=true;
            }
        }
        if(isFindL==false){
            WhoWin=2;
        }
        bool isFindR=false;
        for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                if(rpos[j][i]!=nullptr&&rpos[j][i]->GetStatus()!=DIE){
                    isFindR=true;
                }
            }
        }
        for(int i=0;i<m_RSoldier.size();i++){
            if(m_RSoldier[i]->GetStatus()!=DIE){
                isFindR=true;
            }
        }
        if(isFindR==false){
            WhoWin=1;
        }
    }
    int k=0;
    for(int i=0;i<m_LSoldier.size();i++){
        if(m_LSoldier[i]->GetStatus()==DIE){
            k++;
        }
    }
    if(k!=0)
        qDebug()<<"左侧共有"<<k<<"人死亡"<<endl;
    int j=0;
    for(int i=0;i<m_RSoldier.size();i++){
        if(m_RSoldier[i]->GetStatus()==DIE){
            j++;
        }
    }
    if(j!=0)
        qDebug()<<"右侧共有"<<j<<"人死亡"<<endl;
}
