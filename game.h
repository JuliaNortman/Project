#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game
{
private:
    Player* player1;
    Player* player2;
    Player* currentPlayer;/*who is active at the moment*/
    Board *board;


public:
    Game(Player*, Player*);
    bool endOfGame();
};

#endif // GAME_H
