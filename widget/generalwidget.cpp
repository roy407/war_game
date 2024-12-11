#include "generalwidget.h"

GeneralWidget::GeneralWidget(QList<General*> &v,QWidget *parent)
    : QWidget{parent}
{
    time = new QTimer(this);
    time->start(200);
    Layout = new QVBoxLayout(this);
    if(v.size()==0){
        QLabel* label = new QLabel("没有将领");
        Layout->addWidget(label);
    }else{
        for(int i=0;i<v.size();i++){
            m_Button.push_back(new QPushButton);
            QString soldier;
            if(v[i]->GetSoldier().first==NO_SOLDIER){
                soldier="无兵力";
            }else{
                soldier="有兵力";
            }
            if(v[i]->s.isBusy==true){
                m_Button[i]->setEnabled(false);
            }
            m_Button[i]->setText(v[i]->s.name+"\t"+QString::number(v[i]->s.m_Grade)+"级"+"    "+soldier);
            connect(m_Button[i],&QPushButton::clicked,this,[=](){
                SetGeneral(v[i]);
            });
            Layout->addWidget(m_Button[i]);
            Layout->setAlignment(Qt::AlignTop);
        }
    }
    setLayout(Layout);

    connect(time,&QTimer::timeout,this,&GeneralWidget::UpdateMessage);
}

void GeneralWidget::SetGeneral(General *v)
{
    QDialog dlg;
    QGridLayout GLayout(&dlg);
    QLabel L1("名字："+v->s.name);
    GLayout.addWidget(&L1,0,0);
    QLabel L2("等级："+QString::number(v->s.m_Grade));
    GLayout.addWidget(&L2,0,1);
    QLabel L3("成长："+QString::number(v->s.m_GrowUp));
    GLayout.addWidget(&L3,1,0);
    QLabel L4("武力："+QString::number(v->s.m_Force));
    GLayout.addWidget(&L4,1,1);
    QLabel L5("智力："+QString::number(v->s.m_Intelligence));
    GLayout.addWidget(&L5,2,0);
    QLabel L6("统帅："+QString::number(v->s.m_Commander));
    GLayout.addWidget(&L6,2,1);
    QLabel L7("突围："+QString::number(v->s.m_BreakOut));
    GLayout.addWidget(&L7,3,0);
    QLabel L8("经验值："+QString::number(v->s.m_EmpiricalValue));
    GLayout.addWidget(&L8,3,1);
    QLabel L9("升级所需经验值："+QString::number(v->s.m_TotalEmpiricalValue));
    GLayout.addWidget(&L9,4,0);
    QPushButton* button = new QPushButton;
    GLayout.addWidget(button,4,1);
    connect(button,&QPushButton::clicked,&dlg,[=](){
        emit addSoldier(v);
    });
    if(v->GetSoldier().first==NO_SOLDIER){
        button->setText("添加兵力");
    }else{
        std::pair<SOLDIER,int> so = v->GetSoldier();
        button->setText(V_Soldier::v_name[(int)so.first-1]+"  "+QString::number(so.second)+"人");
    }
    dlg.exec();
}

void GeneralWidget::UpdateMessage()
{
//    if(v.size()==0){
//        QLabel* label = new QLabel("没有将领");
//        Layout->addWidget(label);
//    }else{
//        for(int i=0;i<v.size();i++){
//            m_Button.push_back(new QPushButton);
//            QString soldier;
//            if(v[i]->GetSoldier().first==NO_SOLDIER){
//                soldier="无兵力";
//            }else{
//                soldier="有兵力";
//            }
//            if(v[i]->s.isBusy==true){
//                m_Button[i]->setEnabled(false);
//            }
//            m_Button[i]->setText(v[i]->s.name+"\t"+QString::number(v[i]->s.m_Grade)+"级"+"    "+soldier);
//            connect(m_Button[i],&QPushButton::clicked,this,[=](){
//                SetGeneral(v[i]);
//            });
//            Layout->addWidget(m_Button[i]);
//            Layout->setAlignment(Qt::AlignTop);
//        }
//    }
}
