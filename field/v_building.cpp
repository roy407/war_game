#include "v_building.h"

V_Building::V_Building()
{
    m_Treasure = nullptr;
    m_Crop = nullptr;
    m_Population = nullptr;
    m_Grade=-1; //0-9，但对外显示为1-10
    timer=time[m_Grade+1];
    isBusy = false;
}

void V_Building::SetResource(int* t,int* c,int* p,int* ts,int* cs,QList<V_Soldier*> *Soldier,QList<General*> *General)
{
    m_Treasure = t;
    m_Crop = c;
    m_Population = p;
    m_TreasureSpeed = ts;
    m_CropSpeed = cs;
    m_Soldier = Soldier;
    m_General = General;
    if(m_Building==HOUSE){
        *m_Population+=100;
    }else if(m_Building==FARM){
        *m_CropSpeed+=150;
    }else if(m_Building==BUSINESS_CENTER){
        *m_TreasureSpeed+=100;
    }

}

void V_Building::SetStatus(BUILDING building)
{
    m_Building = building;
}

BUILDING V_Building::GetStatus() const
{
    return m_Building;
}

void V_Building::UpGrade()
{
    if(timer!=0){
        isBusy=true;
        static int t = 0;
        if(t == 2){
            t = 0;
            timer--;
            if(timer==0){
                m_Grade+=1;
            }
        }else{
            t ++;
        }
        update();
    }else{
        isBusy = false;
    }
}

QList<QString> V_Building::v_name={"商业中心","房屋","农场","步兵训练中心","骑兵训练中心","战车制造中心","招贤馆"};
int V_Building::time[10]={3,30,300,1000,3000,5000,10000,15000,20000,50000};

QRectF V_Building::boundingRect() const
{
    return QRectF(-50,-30,100,60);
}

void V_Building::advance(int phase)
{
    if(!phase)return;
    UpGrade();
}

void V_Building::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(-50,0,name);
    if(timer!=0){
        int second = timer%60;
        int minute = timer/60%60;
        int hour = timer/3600;
        QString str = QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second);
        painter->drawText(-50,20,str);
    }
}

V_House::V_House()
{
    name=v_name[1];
    m_Building = HOUSE;
    isArmy = false;
}

int V_House::GetData()
{
    return m_Data[m_Grade+1];
}

V_Tank_Manufacturing_Center::V_Tank_Manufacturing_Center()
{
    name=v_name[5];
    m_Building = TANK_MANUFACTURING_CENTER;
    isArmy = true;
}

V_Cavalry_Training_Center::V_Cavalry_Training_Center()
{
    name=v_name[4];
    m_Building = CAVALRY_TRAINING_CENTER;
    isArmy = true;
}

V_Infantry_Training_Center::V_Infantry_Training_Center()
{
    name=v_name[3];
    m_Building = INFANTRY_TRAINING_CENTER;
    isArmy = true;
}

V_Farm::V_Farm()
{
    name=v_name[2];
    m_Building = FARM;
    isArmy = false;
}

int V_Farm::GetData()
{
    return m_Speed[m_Grade+1];
}


V_Business_Center::V_Business_Center()
{
    name=v_name[0];
    m_Building = BUSINESS_CENTER;
    isArmy = false;
}

int V_Business_Center::GetData()
{
    return m_Speed[m_Grade+1];
}

V_FBuilding::V_FBuilding()
{
    QTimer* time = new QTimer(this);
    time->start(1000);    //军队制造速度
    connect(time,SIGNAL(timeout()),this,SLOT(updateMessage()));
}

int V_FBuilding::SoldierTime[10]={1,2,3,4,5,6,7,8,9,10};

void V_FBuilding::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QDialog dlg;
        QLabel label1;
        QPushButton button1;
        QHBoxLayout* layout1 = new QHBoxLayout;
        QLabel label2;
        QPushButton button2;
        QHBoxLayout* layout2 = new QHBoxLayout;
        QLabel label3;
        QPushButton button3;
        QHBoxLayout* layout3 = new QHBoxLayout;
        QLabel label4;
        QPushButton button4;
        QHBoxLayout* layout4 = new QHBoxLayout;
        QVBoxLayout layout;
        layout1->addWidget(&label1);
        layout1->addWidget(&button1);
        layout2->addWidget(&label2);
        layout2->addWidget(&button2);
        layout3->addWidget(&label3);
        layout3->addWidget(&button3);
        layout4->addWidget(&label4);
        layout4->addWidget(&button4);
        switch(m_Building)
        {
        case INFANTRY_TRAINING_CENTER:
            label1.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button1.setText("招募");
            label2.setText("轻步兵\t攻击力:20\t防御力:8\t生命力:450\n攻击速度:12\t移动速度:7\t占用人口:1\n需要粮食:96\t需要铜钱:33\t需要时间:00:00:16");
            button2.setText("招募");
            label3.setText("重步兵\t攻击力:45\t防御力:22\t生命力:850\n攻击速度:6\t移动速度:4\t占用人口:1\n需要粮食:158\t需要铜钱:92\t需要时间:00:00:37");
            button3.setText("招募");
            label4.setText("近卫兵\t攻击力:50\t防御力:18\t生命力:1200\n攻击速度:10\t移动速度:6\t占用人口:1\n需要粮食:300\t需要铜钱:138\t需要时间:00:01:28");
            button4.setText("招募");
            QObject::connect(&button2,&QPushButton::clicked,&dlg,[=](){
                bool ok;
                int value = QInputDialog::getInt(nullptr, "输入框", "请输入整数：", 0, -10000, 10000, 1, &ok);
                if(ok){
                    que.enqueue({LIGHTCAVALRY,value});
                }
            });
            break;
        case CAVALRY_TRAINING_CENTER:
            label1.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button1.setText("招募");
            label2.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button2.setText("招募");
            label3.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button3.setText("招募");
            label4.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button4.setText("招募");
            break;
        case TANK_MANUFACTURING_CENTER:
            label1.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button1.setText("招募");
            label2.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button2.setText("招募");
            label3.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button3.setText("招募");
            label4.setText("民兵\t攻击力:8\t防御力:1\t生命力:100\n攻击速度:6\t移动速度:7\t占用人口:1\n需要粮食:45\t需要铜钱:7\t需要时间:00:00:05");
            button4.setText("招募");
            break;
        case TAVERN:
            label1.setText("普通招募");   //40-60
            button1.setText("招募");
            label2.setText("精致招募");   //60-75
            button2.setText("招募");
            label3.setText("优秀招募");   //75-85
            button3.setText("招募");
            label4.setText("名将招募");   //85-100,名将加成
            button4.setText("招募");
            QObject::connect(&button1,&QPushButton::clicked,&dlg,[=](){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "确认", "招募需要花费2000铜钱", QMessageBox::Yes|QMessageBox::No);
                // 根据用户的选择执行相应的操作
                if (reply == QMessageBox::Yes) {
                    if(*m_Treasure>=2000){
                        *m_Treasure-=2000;
                        General* r = new General(0);
                        m_General->push_back(r);
                    }else{
                        QMessageBox::information(nullptr,"注意","铜钱不足");
                    }
                }
            });
            QObject::connect(&button2,&QPushButton::clicked,&dlg,[=](){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "确认", "招募需要花费20000铜钱", QMessageBox::Yes|QMessageBox::No);
                // 根据用户的选择执行相应的操作
                if (reply == QMessageBox::Yes) {
                    if(*m_Treasure>=20000){
                        *m_Treasure-=20000;
                        General* r = new General(1);
                        m_General->push_back(r);
                    }else{
                        QMessageBox::information(nullptr,"注意","铜钱不足");
                    }
                }
            });
            QObject::connect(&button3,&QPushButton::clicked,&dlg,[=](){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "确认", "招募需要花费200000铜钱", QMessageBox::Yes|QMessageBox::No);
                // 根据用户的选择执行相应的操作
                if (reply == QMessageBox::Yes) {
                    if(*m_Treasure>=200000){
                        *m_Treasure-=200000;
                        General* r = new General(2);
                        m_General->push_back(r);
                    }else{
                        QMessageBox::information(nullptr,"注意","铜钱不足");
                    }
                }
            });
            QObject::connect(&button4,&QPushButton::clicked,&dlg,[=](){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "确认", "招募需要花费2000000铜钱", QMessageBox::Yes|QMessageBox::No);
                // 根据用户的选择执行相应的操作
                if (reply == QMessageBox::Yes) {
                    if(*m_Treasure>=2000000){
                        *m_Treasure-=2000000;
                        General* r = new General(3);
                        m_General->push_back(r);
                    }else{
                        QMessageBox::information(nullptr,"注意","铜钱不足");
                    }
                }
            });
            break;
        };
        layout.addLayout(layout1);
        layout.addLayout(layout2);
        layout.addLayout(layout3);
        layout.addLayout(layout4);
        dlg.setLayout(&layout);
        dlg.exec();
        //layout还真奇怪，这样就好了
        delete layout1;
        delete layout2;
        delete layout3;
        delete layout4;
    }
}

void V_FBuilding::advance(int phase)
{
    if(!phase)return;
    V_Building::advance(phase);
}

void V_FBuilding::updateMessage()
{
    static int count = 0;
    static std::pair<SOLDIER,int> p;
    while(!que.isEmpty()){
        qDebug()<<"circle entered"<<endl;
        if(count==0){
            p = que.dequeue();
            count=p.second; //右值之后代表总量，不再改变
            break;
        }
    }
    while(count!=0){
        static int tr=0;
        if(tr==SoldierTime[int(p.first)]){
            tr=0;
            //此时军队增加
            count--;
            for(int i=0;i<(*m_Soldier).size();i++){
                if((*m_Soldier)[i]->GetSStatus()==p.first){
                    (*m_Soldier)[i]->AddPopulation(1);
                }
            }
            break;
        }else{
            tr++;
        }
    }
}

void V_NBuilding::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //消耗的财富值该怎么搞？？？
    //答：已经传值进来了
    Q_UNUSED(event);
    QDialog dlg;
    QPushButton button("升级");
    QObject::connect(&button,&QPushButton::clicked,&dlg,[=](){
        if(isBusy==false){
            if(timer==0){
                if(m_Grade==9){
                    QMessageBox::information(nullptr,"注意","该建筑物等级已达最大值");
                }else{
                    m_Grade+=1;
                    timer=time[m_Grade+1];
                    if(m_Building==HOUSE){
                        *m_Population+=GetData();
                    }else if(m_Building==FARM){
                        *m_CropSpeed+=GetData();
                    }else if(m_Building==BUSINESS_CENTER){
                        *m_TreasureSpeed+=GetData();
                    }
                }
            }else if(timer!=0){
                QMessageBox::information(nullptr,"注意","建筑还在升级中");
            }
        }else{
            QMessageBox::information(nullptr,"注意","建筑目前在忙");
        }
    });
    QLabel label1("等级："+QString::number(m_Grade+1));
    QLabel label2("建筑物"+name+"的生产速度为"+QString::number(GetData()));
    QVBoxLayout layout;
    layout.addWidget(&label1);
    layout.addWidget(&label2);
    layout.addSpacing(10);
    layout.addWidget(&button);
    dlg.setLayout(&layout);
    dlg.exec();
}

V_Tavern::V_Tavern()
{
    name=v_name[6];
    m_Building = TAVERN;
    isArmy = true;
}
