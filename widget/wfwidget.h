#ifndef WFWIDGET_H
#define WFWIDGET_H

#include <QWidget>
#include <QTimer>

#include "myscene.h"
#include "city/v_city.h"

class WFWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WFWidget(MyScene* scene,QWidget *parent = nullptr);
private slots:
    void updateMessage();
private:
    QTimer* time;
    MyScene* m_scene;
signals:
    void CityChanged(V_City*);
};

#endif // WFWIDGET_H
