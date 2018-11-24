#include "mainwindow.h"
#include <QApplication>
#include "board.h"
#include "field.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Board *b = new Board;
    b->show();
    //w.show();

    return a.exec();
}
