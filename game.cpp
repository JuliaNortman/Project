#include "game.h"
#include "QEventLoop"
#include <QWaitCondition>

Game::Game(Player* pl1, Player* pl2)
    :player1(pl1), player2(pl2)
{
    //if(player1->getColor() == Color::BLACK) qDebug("black");
    //else qDebug("white");
    if(player1->isBot())board = new Board(player2);
    else board = new Board(player1);
    board->show();
    player1->setBoard(board);
    player2->setBoard(board);
    //QObject::connect(board, &Board::moved, this, &Game::play);
    connect(board, SIGNAL(moved(Player*)), this, SLOT(play(Player*)));
    if(player1->isBot())
    {
        //qDebug("bot first move");
        //player1->move();
        play(player1);
    }

}

bool Game::endOfGame()
{
    return gameEnd;
}

void Game::play(Player* currentPlayer)
{
    //qDebug("Slot");
    /*if(currentPlayer == player1) qDebug("PLAYER1");
    else if(currentPlayer == player2) qDebug("PLAYER2");*/
    int score = 0;
    if(player1->isBot()) score = board->evaluateBoard(player1->getColor());
    else score = board->evaluateBoard(player2->getColor());
    if(!currentPlayer->getCanMove())
    {
        //qDebug("end of current player moves");
        if(currentPlayer == player1)
        {
            board->setCurrentPlayer(player2);
            currentPlayer = player2;
            //qDebug("player2");
            //if(player2->getColor() == Color::BLACK) qDebug("black player");
            //else qDebug("white player");
        }
        else
        {
             board->setCurrentPlayer(player1);
             currentPlayer = player1;
             //qDebug("player1");
        }
        currentPlayer->setCanMove(true);
        gameEnd = board->gameEnd(currentPlayer->getColor());
        if(endOfGame()) return;
    }
    board->setCurrentPlayer(currentPlayer);
    //if(currentPlayer->getColor() == Color::BLACK) qDebug("black current player");
   // else if(currentPlayer->getColor() == Color::WHITE) qDebug("white current player");
    currentPlayer->move();
}
