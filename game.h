#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game :public QObject
{
       Q_OBJECT
private:
    Player* player1;
    Player* player2;
    Board *board;

public:
    Game(Player*, Player*);

public slots:
    void play(Player*);
    void gameEndWindow();

};

#endif // GAME_H
