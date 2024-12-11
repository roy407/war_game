#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("game");
    QIcon icon(":/resource/Empire.ico");
    w.setWindowIcon(icon);
    return a.exec();
}
