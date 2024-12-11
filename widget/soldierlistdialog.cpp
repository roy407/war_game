#include "soldierlistdialog.h"

SoldierListDialog::SoldierListDialog(V_Player* player,int id)
{
    for(int i=0;i<player->m_Field.size();i++){
        if(player->m_Field[i]->id==id){
            field = player->m_Field[i];
            general = field->GetGeneral();
            v = field->GetSoldier();
            break;
        }
    }
    Layout = new QVBoxLayout;
    button = new QPushButton("确认");
    for(int i=0;i<general.size();i++){
        m_Layout.push_back(new QHBoxLayout);
        m_Label.push_back(new QLabel(general[i]->s.name));
        m_Button.push_back(new QPushButton);
        m_CheckBox.push_back(new QCheckBox("出征"));
        if(general[i]->GetSoldier().first==NO_SOLDIER){
            m_Button[i]->setText("添加兵力");
        }else{
            std::pair<SOLDIER,int> so = general[i]->GetSoldier();
            m_Button[i]->setText(V_Soldier::v_name[(int)so.first-1]+"  "+QString::number(so.second)+"人");
        }
        connect(m_Button[i],&QPushButton::clicked,this,[=](){
            SoldierDialog dlg(v,general[i]->GetSoldier(),general[i]->m_Population);
            dlg.exec();
            general[i]->m_Soldier = dlg.GetSoldier();
        });
        m_Layout[i]->addWidget(m_Label[i]);
        m_Layout[i]->addWidget(m_Button[i]);
        m_Layout[i]->addWidget(m_CheckBox[i]);
        Layout->addLayout(m_Layout[i]);
    }
    connect(button,&QPushButton::clicked,this,[=](){
        for(int i=0;i<m_CheckBox.size();i++){
            if(m_CheckBox[i]->isChecked()){
                out_general.push_back(general[i]);
                general[i]->s.isBusy = true;
                close();
            }
        }
    });
    Layout->addWidget(button);
    setLayout(Layout);
}

QList<General *> SoldierListDialog::GetOutGeneral()
{
    return out_general;
}
