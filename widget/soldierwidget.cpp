#include "soldierwidget.h"

SoldierWidget::SoldierWidget(QList<V_Soldier*> &v,QWidget *parent)
    : QWidget{parent}
{
    Layout = new QVBoxLayout(this);
    for(int i=0;i<v.size();i++){
        if(v[i]->GetPopulation()!=0){
            QPushButton* button = new QPushButton;
            QString name = v[i]->GetName();
            QString poputation ="共"+QString::number(v[i]->GetPopulation())+"人";
            button->setIcon(QIcon(v[i]->GetLPhotoPath()));
            button->setText(name+"\t\t"+poputation);
            m_Button.push_back(button);
        }
    }
    if(m_Button.size()==0){
        QLabel* label = new QLabel("没有空闲士兵");
        Layout->addWidget(label);
    }else{
        for(int i=0;i<m_Button.size();i++){
            Layout->addWidget(m_Button[i]);
            Layout->setAlignment(Qt::AlignTop);
        }
    }
    setLayout(Layout);
}
