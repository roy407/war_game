#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QWidget>
#include <QTimer>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>

#include "myview.h"
#include "myscene.h"
#include "city/v_provincial_capital.h"
#include "city/v_capital.h"
#include "map.h"
#include "v_player.h"
#include "communicate.h"
#include "widget/wfwidget.h"
#include "widget/mywidget.h"
#include "widget/fwidget.h"
#include "widget/personaldialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetSceneIndex(MyScene* scene,QWidget* parent,int index);
    void initMenu();
private slots:
    void updateMessage();  //这个逐渐变为主函数了？😀
    void HasBuiltMessage(int id);
    void BuildMessage(V_City* city);
    void AttackMessage(V_City* city);
    void ShowPersonMessage();   //展示玩家完整信息
    void SetFightVisible(bool enable);
    void SetBackWorld();
    void Task();
    void SetQueue(QList<General*> out_general,int id,int time);
private:
    Ui::MainWindow *ui;
    QTimer *timer500,*timer100;
    Map* map;
    MyScene* WorldAFieldScene;
    MyScene* FightScene;
    MyView* WorldAFieldView;
    MyView* FightView;
    WFWidget* WorldAFieldWidget;
    FWidget* FightWidget;
    MyWidget* MessageWidget;
    V_Player* player;   //玩家类，但也不仅限于玩家，之后可以作为NPC
};
#endif // MAINWINDOW_H
