#include "fieldlistdialog.h"

FieldListDialog::FieldListDialog(V_Player* player)
{
    Layout = new QVBoxLayout;
    for(int i=0;i<player->m_Field.size();i++){
        m_Button.push_back(new QPushButton(player->m_Field[i]->GetName()));
        Layout->addWidget(m_Button[i]);
        connect(m_Button[i],&QPushButton::clicked,this,[&](){
            QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
            if (senderButton) {
                for(int il=0;il<m_Button.size();il++){
                    if(senderButton==m_Button[il]){
                        id = player->m_Field[il]->id;
                        SoldierListDialog dlg(player,id);
                        dlg.exec();
                        out_general = dlg.GetOutGeneral();
                        close();
                    }
                }
            }
        });
    }
    setLayout(Layout);
}

int FieldListDialog::GetID() const
{
    return id;
}

QList<General *> FieldListDialog::GetOutGeneral()
{
    return out_general;
}
