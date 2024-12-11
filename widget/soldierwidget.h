#ifndef SOLDIERWIDGET_H
#define SOLDIERWIDGET_H

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

#include "soldier/v_soldier.h"

class SoldierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SoldierWidget(QList<V_Soldier*> &v,QWidget *parent = nullptr);
private:
    QVBoxLayout* Layout;
    QList<QPushButton*> m_Button;
signals:

};

#endif // SOLDIERWIDGET_H
