#ifndef SOLDIERLISTDIALOG_H
#define SOLDIERLISTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>
#include <QListView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QStackedLayout>
#include <QCheckBox>

#include "v_player.h"
#include "soldierdialog.h"

class SoldierListDialog : public QDialog
{
public:
    SoldierListDialog(V_Player* player,int id);
    QList<General*> GetOutGeneral();
private:

    QVBoxLayout* Layout;
    QList<QLabel*> m_Label;
    QList<QPushButton*> m_Button;
    QList<QCheckBox*> m_CheckBox;
    QList<QHBoxLayout*> m_Layout;
    QPushButton* button;
    V_field* field;
    QList<General*> general;
    QList<V_Soldier*> v;
    QList<General*> out_general;
};

#endif // SOLDIERLISTDIALOG_H
