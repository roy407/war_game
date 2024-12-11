#ifndef PERSONALDIALOG_H
#define PERSONALDIALOG_H

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

#include "v_player.h"

class PersonalDialog : public QDialog
{
public:
    PersonalDialog(V_Player* player);
private:
    V_Player* player;
    QTimer* time;
    QList<QLabel*> label_M;
private slots:
    void UpdateMessage();
};

#endif // PERSONALDIALOG_H
