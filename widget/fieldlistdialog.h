#ifndef FIELDLISTDIALOG_H
#define FIELDLISTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "v_player.h"
#include "soldierlistdialog.h"

class FieldListDialog : public QDialog
{
public:
    FieldListDialog(V_Player* player);
    int GetID() const;
    QList<General*> GetOutGeneral();
private:
    QList<QPushButton*> m_Button;
    int id;
    QVBoxLayout* Layout;
    QList<General*> out_general;
};

#endif // FIELDLISTDIALOG_H
