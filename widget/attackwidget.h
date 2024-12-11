#ifndef ATTACKWIDGET_H
#define ATTACKWIDGET_H

#include <QWidget>

#include "map.h"

class AttackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AttackWidget(Map* map,QWidget *parent = nullptr);
private:
    Map* m_Map;
signals:

};

#endif // ATTACKWIDGET_H
