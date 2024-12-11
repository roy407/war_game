#include "wfwidget.h"

WFWidget::WFWidget(MyScene* scene,QWidget *parent)
    : QWidget{parent}
{
    m_scene = scene;
    time = new QTimer(this);
    time->start(30);
    connect(time,SIGNAL(timeout()),this,SLOT(updateMessage()));
}

void WFWidget::updateMessage()
{
    QList<V_City*> m = m_scene->GetMap()->GetCity();
    for(int i=0;i<m.size();i++){
        if(m[i]->type()==V_CITY&&m[i]->isClicked==true){
            m[i]->isClicked=false;
            emit CityChanged(m[i]);
            //qDebug()<<QString::number(i)<<"clicked!"<<endl;
        }
    }
}
