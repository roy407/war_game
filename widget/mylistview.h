#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QListView>
#include <QMimeData>
#include <QDrag>

class MyListView : public QListView
{
public:
    MyListView();
private:
    void startDrag(Qt::DropActions supportedActions) override;
};

#endif // MYLISTVIEW_H
