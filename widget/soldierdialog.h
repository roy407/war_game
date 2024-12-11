#ifndef SOLDIERDIALOG_H
#define SOLDIERDIALOG_H

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

#include "soldier/v_soldier.h"

class SoldierDialog : public QDialog
{
public:
    SoldierDialog(QList<V_Soldier*>& v,std::pair<SOLDIER,int> s,int num);
    std::pair<SOLDIER,int> GetSoldier();
private:
    std::pair<SOLDIER,int> m_Soldier;
    QList<QHBoxLayout*> m_Layout;
    QList<QLabel*> m_Label;
    QList<QPushButton*> m_Button;
    QList<QSlider*> m_Slider;
    QList<QSpinBox*> m_SpinBox;
    QVBoxLayout* VLayout;
};

#endif // SOLDIERDIALOG_H
