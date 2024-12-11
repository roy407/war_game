#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget{parent}
{
    status=NO_MESSAGE;
    Layout = new QVBoxLayout(this);
    city=nullptr;
    field=nullptr;
}

void MyWidget::SetCity_M(V_City* c)
{
    status=V_CITY_MESSAGE;
    m_City = c;
    remove();
    city = new CityMessageWidget(c->s,&status);
    Layout->addWidget(city);
    connect(city,SIGNAL(HasBuiltMessage()),this,SLOT(HasBuilt()));
    connect(city,SIGNAL(BuildMessage()),this,SLOT(Build()));
    connect(city,SIGNAL(AttackMessage()),this,SLOT(Attack()));
}

void MyWidget::SetAttack(V_City *c)
{
    status = ATTACK_MESSAGE;
    remove();
    FieldListDialog dlg(m_Player);
    dlg.exec();
    int id = dlg.GetID();
    int time = m_Map->GetPath(id,c->GetID());
    QList<General*> out_general = dlg.GetOutGeneral();
    AttackWidget* attack = new AttackWidget(m_Map);
    emit SetQueue(out_general,c->GetID(),time);   //为了增加战斗细节，之后可以增加传输的
    //id，用于标识战斗位置，如果有多场战斗，此就作为战场的id
    Layout->addWidget(attack);
}

void MyWidget::HasBuilt()
{
    emit HasBuiltMessage(m_City->GetID());
}

void MyWidget::Build()
{
    emit BuildMessage(m_City);
}

void MyWidget::Attack()
{
    emit AttackMessage(m_City);
}

//缺少东西，应该还要添加军队界面
void MyWidget::SetField(QList<General*> &general,QList<V_Soldier*> &soldier)
{
    //默认为Field_MESSAGE
    status=HASBUILT_MESSAGE;
    remove();
    field = new FieldMessageWidget(general,soldier,&status);
    Layout->addWidget(field);
}

void MyWidget::SetStatus(MESSAGE_STATUS s)
{
    status = s;
    if(s==NO_MESSAGE){
        remove();
    }
}

void MyWidget::setMap(Map *map)
{
    m_Map = map;
}

void MyWidget::setPlayer(V_Player *player)
{
    m_Player = player;
}

MESSAGE_STATUS MyWidget::GetStatus() const
{
    return status;
}

void MyWidget::remove()
{
    QLayout *existingLayout = layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // 清理布局中的项目
            delete item;
        }
    }
}

void CityMessageWidget::button_M_Click()
{
    if(button_M->text()=="创建封地"){
        *status=BUILD_MESSAGE;
        emit BuildMessage();
    }else if(button_M->text()=="进入封地"){
        *status=HASBUILT_MESSAGE;
        emit HasBuiltMessage();
    }else if(button_M->text()=="攻占"){
        *status=ATTACK_MESSAGE;
        emit AttackMessage();
    }
}

CityMessageWidget::CityMessageWidget(City_M s,MESSAGE_STATUS* t,QWidget *parent)
{
    status = t;
    Layout = new QGridLayout;
    for(int i=0;i<7;i++){
        label_M.push_back(new QLabel);
        label_M[i]->setAlignment(Qt::AlignCenter);
        Layout->addWidget(label_M[i],i/2,i%2);
    }
    button_M = new QPushButton(this);
    Layout->addWidget(button_M,3,2);
    connect(button_M,SIGNAL(clicked(bool)),this,SLOT(button_M_Click()));
    label_M[0]->setText("名字："+s.name);
    label_M[1]->setText("规模："+s.size);
    label_M[2]->setText("国家："+s.country);
    label_M[3]->setText("城主："+s.owner);
    label_M[4]->setText("天赋："+s.talent);
    label_M[5]->setText("税率："+QString::number(s.tax));
    label_M[6]->setText("封地："+QString::number(s.manor));
    if(s.isHave){
        if(s.hasfield)
            button_M->setText("进入封地");
        else
            button_M->setText("创建封地");
    }else{
        button_M->setText("攻占");
    }
    setLayout(Layout);
}

FieldMessageWidget::FieldMessageWidget(QList<General *> &general, QList<V_Soldier *> &soldier,MESSAGE_STATUS* s, QWidget *parent)
{
    status = s;
    for(int i=0;i<3;i++){
        m_Button.push_back(new QPushButton);
    }
    m_Button[0]->setText("建筑");
    m_Button[1]->setText("将领");
    m_Button[2]->setText("空闲军队");
    HLayout = new QHBoxLayout;
    for(int i=0;i<3;i++){
        HLayout->addWidget(m_Button[i]);
    }
    VLayout = new QVBoxLayout;
    MainLayout = new QStackedLayout;
    ListView1 = new MyListView();
    ListView2 = new GeneralWidget(general);
    ListView3 = new SoldierWidget(soldier);
    MainLayout->addWidget(ListView1);
    MainLayout->addWidget(ListView2);
    MainLayout->addWidget(ListView3);
    model = new QStandardItemModel(this);
    //之后要进行修改，加入图标
    for(int i=0;i<V_Building::v_name.size();i++){
        model->appendRow(new QStandardItem(V_Building::v_name[i]));
    }
    ListView1->setModel(model);
    ListView1->setDragEnabled(true);
    //不能捕获静态变量和类成员函数
    QObject::connect(m_Button[0],&QPushButton::clicked,MainLayout,[this](){
        MainLayout->setCurrentIndex(0);
        *status = HASBUILT_MESSAGE;
    });
    QObject::connect(m_Button[1],&QPushButton::clicked,MainLayout,[this](){
        MainLayout->setCurrentIndex(1);
        *status = GENERAL_MESSAGE;
    });
    QObject::connect(m_Button[2],&QPushButton::clicked,MainLayout,[this](){
        MainLayout->setCurrentIndex(2);
        *status = SOLDIER_MESSAGE;
    });

    connect(ListView2,&GeneralWidget::addSoldier,this,[&](General* v){
        SoldierDialog dlg(soldier,v->GetSoldier(),v->m_Population);
        dlg.exec();
        v->SetSoldier(dlg.GetSoldier());
    });
    VLayout->addLayout(HLayout);
    VLayout->addLayout(MainLayout);
    setLayout(VLayout);
}
