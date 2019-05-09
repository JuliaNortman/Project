#include "game.h"
#include "start.h"
#include "QEventLoop"
#include <QWaitCondition>
#include <QMessageBox>

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
    connect(board, SIGNAL(end()), this, SLOT(gameEndWindow()));
    if(player1->isBot())
    {
        //qDebug("bot first move");
        //player1->move();
        play(player1);
    }

}


void Game::play(Player* currentPlayer)
{
    qDebug("Slot");
    /*if(currentPlayer == player1) qDebug("PLAYER1");
    else if(currentPlayer == player2) qDebug("PLAYER2");*/
    /*int score = 0;
    if(player1->isBot()) score = board->evaluateBoard(player1->getColor());
    else score = board->evaluateBoard(player2->getColor());*/
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

    }
    board->setCurrentPlayer(currentPlayer);
    /*gameEnd = board->gameEnd(currentPlayer->getColor());
    if(endOfGame())
    {
        gameEndWindow();
        return;
    }*/
    //if(currentPlayer->getColor() == Color::BLACK) qDebug("black current player");
   // else if(currentPlayer->getColor() == Color::WHITE) qDebug("white current player");

    currentPlayer->move();
}

void Game::gameEndWindow()
{
    bool victory = true;
    if(player1->getColor() == Color::WHITE)
    {
        if(board->getWhiteNumber() == 0 || (board->getWhiteMove().empty() && board->getWhiteBeat().empty()))
        {
            victory = false;
        }
        else//(board->getBlackNumber() == 0 || board->getBlackMove().empty() || board->getBlackBeat().empty())
        {
            victory = true;
        }
    }
    else
    {
        if(board->getBlackNumber() == 0 ||(board->getBlackMove().empty() && board->getBlackBeat().empty()))
        {
            victory = false;
        }
        else
        {
            victory = true;
        }
    }
    QMessageBox *mb = new QMessageBox;
    if(victory) mb->setText("Congratulations! \nYou have won");
    else mb->setText("Ooops, you have lost...\n");
    QAbstractButton *restart = mb->addButton(tr("Restart"), QMessageBox::YesRole);
    QAbstractButton *quit = mb->addButton(tr("Quit"), QMessageBox::NoRole);
    mb->exec();
    if(mb->clickedButton() == restart)
    {
        board->~Board();
    }
    else if(mb->clickedButton() == quit)
    {
        mb->close();
        board->close();
        start *game = new start;
        game->show();
        //board->~Board();
    }
    /*if(white == 0 || whiteMove.empty())
    {
        QMessageBox *lost = new QMessageBox;
        lost->setText("Ooops, you have lost...\n");
        QAbstractButton *restart = lost->addButton(tr("Restart"), QMessageBox::YesRole);
        QAbstractButton *quit = lost->addButton(tr("Quit"), QMessageBox::NoRole);
        lost->exec();
        if(lost->clickedButton() == restart)
        {
            white = black = 12;
            active = prevActive = -1;
            whiteBeat = blackBeat = false;
            whiteMove.clear();
            blackMove.clear();
            for(int i = 0; i < 64; ++i)
            {
                fields[i].beat = false;
                fields[i].color = 0;
                fields[i].empty = true;
                fields[i].king = false;
                fields[i].needToBeat = false;
                fields[i].neighbors.clear();
                modelBoard(i);
                lost->close();
            }
        }
        else if(lost->clickedButton() == quit)
        {
            lost->close();
            this->close();
        }*/
}
