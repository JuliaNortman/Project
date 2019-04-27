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
    bool gameEnd = false;


public:
    Game(Player*, Player*);
    bool endOfGame();
    void setGameEnd(bool end){gameEnd = end;}

public slots:
    void play(Player*);

};

#endif // GAME_H
