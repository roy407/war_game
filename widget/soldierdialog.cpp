#include "soldierdialog.h"

SoldierDialog::SoldierDialog(QList<V_Soldier*>& v,std::pair<SOLDIER,int> s,int num)
{
    m_Soldier = s;
    VLayout = new QVBoxLayout;
    for(int i=0;i<v.size();i++){
        m_Layout.push_back(new QHBoxLayout);
        m_Label.push_back(new QLabel(v[i]->GetName()));
        m_Button.push_back(new QPushButton("确认"));
        m_Slider.push_back(new QSlider(Qt::Horizontal));
        m_SpinBox.push_back(new QSpinBox);
        if(v[i]->GetPopulation()==0){
            m_Slider[i]->setEnabled(false);
            m_SpinBox[i]->setEnabled(false);
        }
        // 设置滑动条和数字输入框的范围
        m_Slider[i]->setRange(0, v[i]->GetPopulation());
        m_SpinBox[i]->setRange(0, v[i]->GetPopulation());

        // 将滑动条和数字输入框的值绑定在一起
        connect(m_Slider[i], &QSlider::valueChanged, m_SpinBox[i], &QSpinBox::setValue);
        connect(m_SpinBox[i], static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), m_Slider[i], &QSlider::setValue);

        // 将滑动条和数字输入框添加到布局
        m_Layout[i]->addWidget(m_Label[i]);
        m_Layout[i]->addWidget(m_Slider[i]);
        m_Layout[i]->addWidget(m_SpinBox[i]);
        m_Layout[i]->addWidget(m_Button[i]);
        VLayout->addLayout(m_Layout[i]);
        QObject::connect(m_Button[i],&QPushButton::clicked,this,[=](){
            if(m_Soldier.first==v[i]->GetSStatus()){
                if(m_Soldier.second+m_SpinBox[i]->value() > num){
                    QMessageBox::information(nullptr,"注意","人数超出最大值");
                    return;
                }
                m_Soldier.second+=m_SpinBox[i]->value();
                v[i]->ReducePopulation(m_SpinBox[i]->value());
            }else{
                if(m_SpinBox[i]->value() > num){
                    QMessageBox::information(nullptr,"注意","人数超出最大值");
                    return;
                }
                if(m_Soldier.first!=NO_SOLDIER){
                    for(int jk=0;jk<v.size();jk++){
                        if(v[jk]->GetSStatus()==m_Soldier.first){
                            v[jk]->AddPopulation(m_Soldier.second);
                            m_Soldier.first =v[i]->GetSStatus();
                            m_Soldier.second=m_SpinBox[i]->value();
                        }
                    }
                }else{
                    m_Soldier.first=v[i]->GetSStatus();
                    m_Soldier.second=m_SpinBox[i]->value();
                    v[i]->ReducePopulation(m_SpinBox[i]->value());
                }
            }
            close();
        });
    }
    //在循环中，似乎会发生数组越界的行为，不知道为何
    //答，因为之前用的是引用传递，应该使用值传递
    //后期要用预处理命令更改一下，太冗余且没必要
    setLayout(VLayout);
}

std::pair<SOLDIER,int> SoldierDialog::GetSoldier()
{
    return m_Soldier;
}
