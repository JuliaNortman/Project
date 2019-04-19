#pragma once

#include <QDialog>
#include "field.h"
#include "mainwindow.h"
#include "player.h"
#include "game.h"
#include "settings.h"

namespace Ui {
class start;
}

class Settings;

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();
    void setPlayers(Player*, Player*);
public slots:
    void startGame(int);
private slots:
    void on_toolButton_clicked();

private:
    Ui::start *ui;
    Player* player1 =  nullptr;/*main player*/
    Player* player2 =  nullptr;/*second player*/
    Game* game = nullptr;
    Settings* s;
};

