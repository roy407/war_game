#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "field/v_field.h"

class FieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldWidget(QList<V_field*>& List,QWidget *parent = nullptr);
    QList<QPushButton*> m_Button;
signals:

};

#endif // FIELDWIDGET_H
