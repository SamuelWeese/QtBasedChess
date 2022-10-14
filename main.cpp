#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.generateBoard(8, 8);
    w.setStandardBoard();
    w.show();
    w.showBoard();
    return a.exec();
}
