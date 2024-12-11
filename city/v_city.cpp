#include "v_city.h"

V_City::V_City()
{
    isClicked = false;
    s.isHave=false;
    s.hasfield=false;
}

V_City::~V_City()
{
}

std::pair<int, int> V_City::GetPos() const
{
    return m_Pos;
}

void V_City::SetPos(std::pair<int, int> pos)
{
    m_Pos = pos;
    setPos(m_Pos.first,m_Pos.second);
}

City_M V_City::GetCityMessage() const
{
    return s;
}

V_CITY_SIZE V_City::City_Size()
{
    return size;
}

ITEM_TYPE V_City::type()
{
    return Type;
}

void V_City::SetID(int id)
{
    this->id=id;
}

int V_City::GetID() const
{
    return this->id;
}

void V_City::advance(int phase)
{

}

QRectF V_City::boundingRect() const
{
    return QRectF(-95,-69,191,138);
}

void V_City::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QFont font("宋体", 20); // 设置字体
    QPen pen;
    if(s.isHave)
        pen.setColor(Qt::blue); // 设置画笔颜色
    else
        pen.setColor(Qt::red);
    QBrush b(Qt::black);
    painter->setFont(font);
    painter->setPen(pen);
    painter->setBrush(b);
    painter->drawPixmap(rect.toRect(),QPixmap(m_PhotoPath));
    painter->fillRect(rect.left()+30,rect.top()-50,131,45,b);
    painter->drawText(rect.left(),rect.top()-50,191,50,Qt::AlignCenter,s.name);
}

void V_City::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        isClicked=true;
    }
}
