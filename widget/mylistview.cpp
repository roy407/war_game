#include "mylistview.h"

MyListView::MyListView()
{

}

void MyListView::startDrag(Qt::DropActions supportedActions)
{
    QMimeData *mimeData = new QMimeData;
    // 设置拖拽的数据
    QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty())
        return;
    //获取拖拽的项的数据
    QVariant dragData = selectedIndexes.first().data(Qt::DisplayRole);
    mimeData->setText(dragData.toString());
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}
