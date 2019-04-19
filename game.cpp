#include "game.h"

Game::Game(Player* pl1, Player* pl2)
    :player1(pl1), player2(pl2)
{
    board = new Board(player1);
    board->show();

    while (!endOfGame())
    {
        qDebug("in while");
        while(currentPlayer->getCanMove())
        {
            qDebug("before move");
            currentPlayer->move();
            qDebug("after move");
        }
        if(currentPlayer == player1) currentPlayer = player2;
        else currentPlayer = player1;
        currentPlayer->setCanMove(true);
        board->setCurrentPlayer(currentPlayer);
    }
}

bool Game::endOfGame()
{
    return false;
}
