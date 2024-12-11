#include "field.h"

Field::Field(V_field* field)
{
    m_field = field;
    setPos(0,0);
    setAcceptDrops(true);
}


QRectF Field::boundingRect() const
{
    return QRectF(0,0,1275,471);
}

void Field::advance(int phase)
{

}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(),QPixmap(":/resource/field.png"));
}

void Field::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasText())
        event->acceptProposedAction();
}

void Field::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QString s = event->mimeData()->text();
    QPoint pos = event->pos().toPoint()-QPoint(58,76);
    if(pos.x()<0||pos.x()-160*4>0){return;}
    if(pos.y()<0||pos.y()-110*3>0){return;}
    if(pos.x()>100&&pos.x()<160||pos.x()>260&&pos.x()<320||pos.x()>420&&pos.x()<480)return;
    if(pos.y()>60&&pos.y()<110||pos.y()>170&&pos.y()<220)return;
    if(s==V_Building::v_name[0])
    {
        m_field->AddBuilding(BUSINESS_CENTER,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    else if(s==V_Building::v_name[1])
    {
        m_field->AddBuilding(HOUSE,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    else if(s==V_Building::v_name[2])
    {
        m_field->AddBuilding(FARM,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    else if(s==V_Building::v_name[3])
    {
        m_field->AddBuilding(INFANTRY_TRAINING_CENTER,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    else if(s==V_Building::v_name[4])
    {
        m_field->AddBuilding(CAVALRY_TRAINING_CENTER,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    else if(s==V_Building::v_name[5])
    {
        m_field->AddBuilding(TANK_MANUFACTURING_CENTER,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }else if(s==V_Building::v_name[6]){
        m_field->AddBuilding(TAVERN,58+pos.x()/160*160+50,76+pos.y()/110*110+30);
    }
    update();
}

