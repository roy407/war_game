#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

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
#include <QTimer>

#include "soldier/general.h"

class GeneralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralWidget(QList<General*> &v,QWidget *parent = nullptr);
private:
    void SetGeneral(General* v);
    QVBoxLayout* Layout;
    QList<QPushButton*> m_Button;
    QTimer* time;
private slots:
    void UpdateMessage();
signals:
    void addSoldier(General* v);
};

#endif // GENERALWIDGET_H
