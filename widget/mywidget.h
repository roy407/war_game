#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QListView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QStackedLayout>

#include "communicate.h"
#include "mylistview.h"
#include "field/v_building.h"
#include "generalwidget.h"
#include "soldierwidget.h"
#include "city/v_city.h"
#include "attackwidget.h"
#include "soldierdialog.h"
#include "v_player.h"
#include "fieldlistdialog.h"

class CityMessageWidget;
class FieldMessageWidget;
//城市信息。（封地建筑信息。军队信息。）。进攻其它城市

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
signals:
    void HasBuiltMessage(int id);
    void BuildMessage(V_City* city);
    void AttackMessage(V_City* city);
    void SetQueue(QList<General*> out_general,int id,int time);
private slots:
    void SetCity_M(V_City* c);
    void SetAttack(V_City* c);
    void HasBuilt();
    void Build();
    void Attack();
public:
    void SetField(QList<General*> &general,QList<V_Soldier*> &soldier);
    void SetStatus(MESSAGE_STATUS s);
    void setMap(Map* map);
    void setPlayer(V_Player* player);
    MESSAGE_STATUS GetStatus() const;
    void remove();
private:
    CityMessageWidget* city;
    FieldMessageWidget* field;
    QVBoxLayout* Layout;
    MESSAGE_STATUS status;     //
    V_City* m_City;
    Map* m_Map;
    V_Player* m_Player;
};

class CityMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CityMessageWidget(City_M s,MESSAGE_STATUS* t,QWidget *parent = nullptr);
signals:
    void BuildMessage();
    void HasBuiltMessage();
    void AttackMessage();
private slots:
    void button_M_Click();
private:
    MESSAGE_STATUS* status;
    QList<QLabel*> label_M;
    QPushButton* button_M;
    QGridLayout* Layout;
};

class FieldMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldMessageWidget(QList<General*> &general,QList<V_Soldier*> &soldier,MESSAGE_STATUS* s,QWidget *parent = nullptr);
private:
    MESSAGE_STATUS* status;
    QList<QPushButton*> m_Button;
    QHBoxLayout* HLayout;
    QVBoxLayout* VLayout;
    QStackedLayout* MainLayout;
    MyListView* ListView1;
    GeneralWidget* ListView2;
    SoldierWidget* ListView3;
    QStandardItemModel* model;
};

#endif // MYWIDGET_H
