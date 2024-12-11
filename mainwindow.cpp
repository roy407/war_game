#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer500 = new QTimer(this);
    timer500 -> start(500);      //封地与世界的item更新
    timer100 = new QTimer(this);
    timer100 ->start(30);
    map=new Map();
    WorldAFieldScene = new MyScene(this); //复用这个窗口，代替了FightScene
    WorldAFieldScene -> SetMap(map);
    FightScene = new MyScene(this);
    //显示窗口
    WorldAFieldWidget = new WFWidget(WorldAFieldScene,this);
    WorldAFieldWidget -> setGeometry(10,10,1275,950);
    MessageWidget = new MyWidget(this);
    MessageWidget -> setGeometry(1299,9,491,471);
    MessageWidget -> setMap(map);
    WorldAFieldView = new MyView(WorldAFieldScene,WorldAFieldWidget);
    player = new V_Player(map);
    MessageWidget ->setPlayer(player);
    SetSceneIndex(WorldAFieldScene,WorldAFieldWidget,0);
    connect(timer500,SIGNAL(timeout()),WorldAFieldScene,SLOT(advance()));
    connect(WorldAFieldWidget,SIGNAL(CityChanged(V_City*)),MessageWidget,SLOT(SetCity_M(V_City*)));
    //好诡异啊，自己既是信号发起方，还是信号接受方，真是多此一举
    connect(MessageWidget,SIGNAL(AttackMessage(V_City*)),MessageWidget,SLOT(SetAttack(V_City*)));
    connect(MessageWidget,SIGNAL(HasBuiltMessage(int)),this,SLOT(HasBuiltMessage(int)));
    connect(MessageWidget,SIGNAL(BuildMessage(V_City*)),this,SLOT(BuildMessage(V_City*)));
    connect(MessageWidget,SIGNAL(AttackMessage(V_City*)),this,SLOT(AttackMessage(V_City*)));
    connect(MessageWidget,SIGNAL(SetQueue(QList<General*>,int,int)),this,SLOT(SetQueue(QList<General*>,int,int)));
    //menu init
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetSceneIndex(MyScene* scene,QWidget* parent,int index)
{
    MyView* view=nullptr;
    if(index==0){
        scene->WorldAFieldScene();
        WorldAFieldView->resize(1252,940);
        view=WorldAFieldView;
    }else if(index==1){
        scene->FightScene(player->m_Fight[0]);
        FightView->resize(1752,402);
        view=FightView;
    }
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //隐藏掉滚动条
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::initMenu()
{
    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // 创建文件菜单
    QMenu *fileMenu = menuBar->addMenu(tr("&基本操作"));

    // 添加文件菜单项
    QAction *FightAction = fileMenu->addAction(tr("战斗界面"));
    QAction *saveAction = fileMenu->addAction(tr("新游戏"));
    QAction *personAction = fileMenu->addAction(tr("查看个人信息"));
    QAction *BackWorldAction = fileMenu->addAction(tr("回到主世界"));
    QAction *TaskAction = fileMenu->addAction(tr("任务界面"));
    connect(personAction,SIGNAL(triggered(bool)),this,SLOT(ShowPersonMessage()));
    connect(FightAction,SIGNAL(triggered(bool)),this,SLOT(SetFightVisible(bool)));
    connect(BackWorldAction,SIGNAL(triggered(bool)),this,SLOT(SetBackWorld()));
    connect(TaskAction,SIGNAL(triggered(bool)),this,SLOT(Task()));
}

//该函数废弃，全部使用槽和函数代替
//从这里就能看出，用定时函数实现信号的传递是不合适的
void MainWindow::updateMessage()
{
//    static V_City* city = nullptr;
//    if(WorldAFieldScene->GetStatus()==WORLD){
//        QList<V_City*> m = WorldAFieldScene->GetMap()->GetCity();
//        for(auto& item:m){
//            if(item->type()==V_CITY&&item->isClicked==true){
//                item->isClicked=false;
//                //或许在这个地方可以加入界面的变化？
//                city = item;
//                emit CityClicked
//                MessageWidget->SetCity_M(item->GetCityMessage());
//            }
//        }
////获取哪个城市
//        if(MessageWidget->GetStatus()==HASBUILT_MESSAGE){
//            WorldAFieldView->resetTransform();
//            field = player->m_Field[city->GetID()];
//            field->GetSceneSource(WorldAFieldScene);
//            WorldAFieldScene->SetFieldScene(field);
//            WorldAFieldWidget->setGeometry(10,10,1275,471);
//            WorldAFieldWidget->setAcceptDrops(true);
//            MessageWidget->SetField(field->GetGeneral(),field->GetSoldier()); //设置为封地模式
//        }else if(MessageWidget->GetStatus()==BUILD_MESSAGE){

//        }else if(MessageWidget->GetStatus()==ATTACK_MESSAGE){

//        }
//    }
//    if(WorldAFieldScene->GetStatus()==FIELD){
//        city = nullptr;
    //    }
}

void MainWindow::HasBuiltMessage(int id)
{
    WorldAFieldView->resetTransform();
    V_field* field = nullptr;
    for(int i=0;i<player->m_Field.size();i++){
        if(player->m_Field[i]->id==id){
            field = player->m_Field[i];
        }
    }
    field->GetSceneSource(WorldAFieldScene);
    WorldAFieldScene->SetFieldScene(field);
    WorldAFieldWidget->setGeometry(10,10,1275,471);
    WorldAFieldWidget->setAcceptDrops(true);
    MessageWidget->SetField(field->GetGeneral(),field->GetSoldier()); //设置为封地模式
}

void MainWindow::BuildMessage(V_City *city)
{
    if(player->SetField(city->GetID())){
        QMessageBox::information(nullptr,"成功","新建了一个封地");
    }else{
        QMessageBox::information(nullptr,"失败","封地已达最大值");
    }
}

void MainWindow::AttackMessage(V_City *city)
{

}

void MainWindow::ShowPersonMessage()
{
    PersonalDialog dlg(player);
    dlg.exec();
}

void MainWindow::SetFightVisible(bool enable)
{
    if(FightWidget->isVisible()){
        FightWidget->setVisible(false);
        if(MessageWidget->GetStatus()==V_CITY_MESSAGE){
            WorldAFieldWidget->setGeometry(10,10,1275,900);
            WorldAFieldView->resize(1275,900);
        }
    }else{
        FightWidget->setVisible(true);
        if(MessageWidget->GetStatus()==V_CITY_MESSAGE){
            WorldAFieldWidget->setGeometry(10,10,1275,471);
            WorldAFieldView->resize(1275,471);
        }
    }
    update();
}

void MainWindow::SetBackWorld()
{
    WorldAFieldScene->WorldAFieldScene();
    MessageWidget->SetStatus(NO_MESSAGE);
    WorldAFieldWidget->setGeometry(10,10,1275,950);
    WorldAFieldWidget->setAcceptDrops(false);
}

void MainWindow::Task()
{

}

void MainWindow::SetQueue(QList<General *> out_general, int id,int time)
{
    Fight_Queue* queue = new Fight_Queue;
    queue->general=out_general;
    queue->id = id;
    queue->time = time;
    player->m_Taskque.push_back(queue);
}


