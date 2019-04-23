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
    if(player1->isBot())
    {
        player1->move();
    }

}

bool Game::endOfGame()
{
    return false;
}

void Game::play(Player* currentPlayer)
{
    qDebug("Slot");
    if(endOfGame()) return;
    if(!currentPlayer->getCanMove())
    {
        qDebug("end of current player moves");
        if(currentPlayer == player1)
        {
            board->setCurrentPlayer(player2);
            currentPlayer = player2;
            qDebug("player2");
            if(player2->getColor() == Color::BLACK) qDebug("black player");
            else qDebug("white player");
        }
        else
        {
             board->setCurrentPlayer(player1);
             currentPlayer = player1;
             qDebug("player1");
        }
        currentPlayer->setCanMove(true);
    }
    board->setCurrentPlayer(currentPlayer);
    if(currentPlayer->getColor() == Color::BLACK) qDebug("black current player");
    else qDebug("white current player");
    currentPlayer->move();
}
