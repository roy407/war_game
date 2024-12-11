#include "personaldialog.h"

PersonalDialog::PersonalDialog(V_Player* player)
{
    time = new QTimer(this);
    time -> start(500);
    this->player = player;
    setWindowTitle("个人信息");
    QGridLayout* Layout = new QGridLayout(this);
    for(int i=0;i<5;i++){
        label_M.push_back(new QLabel);
        label_M[i]->setAlignment(Qt::AlignCenter);
        Layout->addWidget(label_M[i],i/2,i%2);
    }
    label_M[0]->setText("钱财："+QString::number(player->m_Treasure));
    label_M[1]->setText("钱财增长速度："+QString::number(player->m_Treasure_Speed)+"每小时");
    label_M[2]->setText("粮食："+QString::number(player->m_Crop));
    label_M[3]->setText("粮食增长速度："+QString::number(player->m_Crop_Speed)+"每小时");
    label_M[4]->setText("人口："+QString::number(player->m_population)+"人");
    connect(time,&QTimer::timeout,this,&PersonalDialog::UpdateMessage);
}

void PersonalDialog::UpdateMessage()
{
    label_M[0]->setText("钱财："+QString::number(player->m_Treasure));
    label_M[1]->setText("钱财增长速度："+QString::number(player->m_Treasure_Speed)+"每小时");
    label_M[2]->setText("粮食："+QString::number(player->m_Crop));
    label_M[3]->setText("粮食增长速度："+QString::number(player->m_Crop_Speed)+"每小时");
    label_M[4]->setText("人口："+QString::number(player->m_population)+"人");
}
