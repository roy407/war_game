#include "map.h"

Map::Map()
{
    m_MaxWidth=5000;
    m_MaxHeight=5000;
    init();
    initRoad();
}

void Map::init()
{
/*目前只生成10*10个地图大小的地图*/
/*目前只能有一个首都，以首都为中心点，越向外城市等级越低*/
/*使用概率来确定城市规模*/
/*使用到首都的绝对距离的倒数乘以一个*/
    QFile* file = new QFile(":/resource/city.txt");
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(file);  // 使用 QTextStream 读取文本
        while (!in.atEnd()) {
            QString line = in.readLine();
            v_name.push_back(line);
        }
        file->close();
    }else{
        qDebug()<<"city name open failed"<<endl;
    }
    int w = 10;
    int h = 10;
    int p_width = m_MaxWidth / w;
    int p_height = m_MaxHeight / h;
    int c_i = 4;
    int c_j = 6;
    int randomh = QRandomGenerator::global()->bounded(100);
    int randomw = QRandomGenerator::global()->bounded(100);
    V_City *capital = new V_Capital;
    capital->s.name=v_name[(c_i-1)*10+c_j];
    capital->SetPos({(c_j-1)*p_height+p_height/2+randomh,(c_i-1)*p_width+p_width/2+randomw});
    capital->SetID((c_i-1)*10+c_j);
    //道路初始化
    m_Road[capital->GetID()].first=capital->GetPos();
    //m_Road[temp->GetID()].second=QHash<int,bool>();
    int p_1[4]={-10,-1,1,10};
    for(int j=0;j<4;j++)
    {
        if(p_1[j]+capital->GetID()>=1&&p_1[j]+capital->GetID()<=100){
            if(abs(p_1[j])<10&&((p_1[j]+capital->GetID())/10!=capital->GetID()/10)) continue;
            m_Road[capital->GetID()].second[p_1[j]+capital->GetID()]=true;
            m_Road[p_1[j]+capital->GetID()].second[capital->GetID()]=true;
        }
    }
    int p_2[4]={-11,-9,9,11};
    for(int j=0;j<4;j++)
    {
        if(p_2[j]+capital->GetID()>=1&&p_2[j]+capital->GetID()<=100){
            if(abs(p_2[j])<10&&((p_2[j]+capital->GetID())/10==capital->GetID()/10)) continue;
            m_Road[capital->GetID()].second[p_2[j]+capital->GetID()]=true;
            m_Road[p_2[j]+capital->GetID()].second[capital->GetID()]=true;
        }
    }
    m_City.push_back(capital);
    for(int i=1;i<=w;i++){
        for(int j=1;j<=h;j++){
            if(!(i==c_i&&j==c_j)){
                int randomh = QRandomGenerator::global()->bounded(100);
                int randomw = QRandomGenerator::global()->bounded(100);
                int t_h = (j-1)*p_height+p_height/2+randomh;
                int t_w = (i-1)*p_width+p_width/2+randomw;
                V_City *temp;
                double probability = QRandomGenerator::global()->generateDouble();
                probability*=1./sqrt(pow(fabs(capital->GetPos().first-t_h),2)+pow(fabs(capital->GetPos().second-t_w),2))*500;
                if(probability >= 0.7) temp = new V_Provincial_Capital;
                else if(probability>=0.2&&probability<0.7) temp = new V_CountyTown;
                else if(probability<0.2) temp = new V_Town;
                else temp = new V_Town;
                temp->s.name=v_name[(i-1)*10+j]; //只有274个地名
                temp->SetPos({t_h,t_w});
                temp->SetID((i-1)*10+j);
                m_City.push_back(temp);
                //道路初始化
                std::pair<std::pair<int,int>,QHash<int,bool>> t;
                m_Road[temp->GetID()].first=temp->GetPos();
                //m_Road[temp->GetID()].second=QHash<int,bool>();
                int p_1[4]={-10,-1,1,10};
                for(int k=0;k<4;k++)  //上下左右的，生成概率为85%
                {
                    double p = QRandomGenerator::global()->generateDouble();
                    if(p_1[k]+temp->GetID()>=1&&p_1[k]+temp->GetID()<=100&&p<=0.85){
                        if((temp->GetID()%10==0&&k==2)||(temp->GetID()%10==1&&k==1)) continue;
                        m_Road[temp->GetID()].second[p_1[k]+temp->GetID()]=true;
                        m_Road[p_1[k]+temp->GetID()].second[temp->GetID()]=true;
                    }
                }
                int p_2[4]={-11,-9,9,11};
                for(int k=0;k<4;k++)  //斜对角线上的，生成概率为40%
                {
                    double p = QRandomGenerator::global()->generateDouble();
                    if(p_2[k]+temp->GetID()>=1&&p_2[k]+temp->GetID()<=100&&p<=0.4){
                        if((temp->GetID()%10==1&&k==2)||(temp->GetID()%10==0&&k==1)) continue;
                        if((temp->GetID()%10==0&&k==0)||(temp->GetID()%10==0&&k==3)) continue;
                        if((temp->GetID()%10==1&&k==0)||(temp->GetID()%10==1&&k==3)) continue;
                        m_Road[temp->GetID()].second[p_2[k]+temp->GetID()]=true;
                        m_Road[p_2[k]+temp->GetID()].second[temp->GetID()]=true;
                    }
                }
            }
        }
    }
}

void Map::initRoad()
{
    QPainterPath path;
    QPen pen;
    pen.setWidth(5);
    auto it = m_Road.begin();
    for(;it!=m_Road.end();it++){
        auto pos = it.value().first;
        path.moveTo(pos.first,pos.second);
        auto ite=it.value().second.begin();
        for(;ite!=it.value().second.end();ite++){
            if(ite.value()==true){
                auto _pos = m_Road[ite.key()].first;
                path.quadTo((pos.first+_pos.first)/2.1,(pos.second+_pos.second)/2.1,_pos.first,_pos.second); // 添加一个二次贝塞尔曲线
                path.moveTo(pos.first,pos.second);
            }
        }
    }
    // 创建路径项并设置路径
    pathItem = new QGraphicsPathItem(path);
    pathItem->setPen(pen);
    // 添加路径项到场景
}

QList<V_City*> Map::GetCity()
{
    return m_City;
}

QGraphicsPathItem* Map::GetRoad()
{
    return pathItem;
}

QHash<int, std::pair<std::pair<int, int>, QHash<int, bool> > > Map::GetARoad() const
{
    return m_Road;
}

QList<General *> Map::GetSoldier(int id)
{
    V_CITY_SIZE size;
    for(int i=0;i<m_City.size();i++){
        if(m_City[i]->GetID()==id){
            size = m_City[i]->City_Size();
            break;
        }
    }
    QList<General*> general;
    switch(size)
    {
    case CAPITAL:
        break;
    case PROVINCIAL_CAPITAL:
        break;
    case COUNTYTOWN:
        break;
    case TOWN:
        for(int i=0;i<5;i++){
            general.push_back(new General(0));
            general[i]->SetSoldier({LIGHTCAVALRY,200});
        }
        general.push_back(new General(1));
        general[5]->SetSoldier({SAGITTARY,200});
        break;
    };
    return general;
}

double Map::GetPath(int start, int end)
{
//    QQueue que;
//    que.enqueue(start);
//    que.enqueue(0);
//    while(!que.isEmpty()){
//        int temp = que.dequeue();

//    }
    QString country_start;
    for(int i=0;i<m_City.size();i++){
        if(m_City[i]->GetID()==start){
            country_start=m_City[i]->s.country;
        }
    }
    for(auto it = m_Road[end].second.begin();it!=m_Road[end].second.end();it++){
        if(it.value()==true)
            for(int i=0;i<m_City.size();i++){
                if(m_City[i]->GetID()==it.key()){
                    if(m_City[i]->s.country==country_start){
                        return 30;
                    }
                }
            }
    }
    return 0;
}

QRect Map::GetSize()
{
    return QRect(0,0,m_MaxWidth,m_MaxHeight);
}

Map::~Map()
{
    for(int i=0;i<m_City.size();i++){
        delete m_City[i];
    }
}
