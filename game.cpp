#include "game.h"
#include "QEventLoop"
#include <QWaitCondition>

Game::Game(Player* pl1, Player* pl2)
    :player1(pl1), player2(pl2)
{
    board = new Board(player1);
    board->show();
    player1->setBoard(board);
    player2->setBoard(board);
    //QObject::connect(board, &Board::moved, this, &Game::play);
    connect(board, SIGNAL(moved(Player*)), this, SLOT(play(Player*)));
    play(player1);

}

bool Game::endOfGame()
{
    return false;
}

void Game::play(Player* currentPlayer)
{
    if(endOfGame()) return;
    if(!currentPlayer->getCanMove())
    {
        if(currentPlayer == player1)
        {
            board->setCurrentPlayer(player2);
            currentPlayer = player2;
        }
        else
        {
             board->setCurrentPlayer(player1);
             currentPlayer = player1;
        }
        currentPlayer->setCanMove(true);
    }
    board->setCurrentPlayer(currentPlayer);
    currentPlayer->move();
}
