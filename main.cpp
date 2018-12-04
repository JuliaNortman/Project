#include "mainwindow.h"
#include <QApplication>
#include "board.h"
#include "field.h"
#include "start.h"


#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    start *game = new start;
    game->show();

    return a.exec();
}
