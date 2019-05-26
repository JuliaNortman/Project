#include "game.h"
#include "start.h"
#include "QEventLoop"
#include <QWaitCondition>
#include <QMessageBox>

/**
 * @brief Constructor
 * @param pl1 White player
 * @param pl2 Balck player
 */
Game::Game(Player* pl1, Player* pl2)
    :player1(pl1), player2(pl2)
{
    /*create board*/
    if(player1->isBot())board = new Board(player2);
    else board = new Board(player1);
    board->show();

    /*set board to each player*/
    player1->setBoard(board);
    player2->setBoard(board);
    connect(board, SIGNAL(moved(Player*)), this, SLOT(play(Player*)));
    connect(board, SIGNAL(end()), this, SLOT(gameEndWindow()));

    player1->setCanMove(true); //allow first player to move
    if(player1->isBot()) play(player1);
}

/**
 * @brief controls the process of playing
 * @param currentPlayer Player who is active at the moment
 */
void Game::play(Player* currentPlayer)
{
    /*active player has made all his moves*/
    if(!currentPlayer->getCanMove())
    {
        //changeactive player
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

        currentPlayer->setCanMove(true);//allow current player to move

    }
    board->setCurrentPlayer(currentPlayer); //set active player to the board
    currentPlayer->move(); //move
}

/**
 * @brief show message box when the game is over
 */
void Game::gameEndWindow()
{
    bool victory = true;
    if(player1->getColor() == Color::WHITE)
    {
        /*if current player has no possible moves left then he has lost*/
        if(board->getWhiteNumber() == 0 || (board->getWhiteMove().empty() && board->getWhiteBeat().empty()))
        {
            victory = false;
        }
        /*else he has won*/
        else victory = true;
    }
    else
    {
        if(board->getBlackNumber() == 0 ||(board->getBlackMove().empty() && board->getBlackBeat().empty()))
        {
            victory = false;
        }
        else victory = true;
    }
    /*creaing message box*/
    QMessageBox *mb = new QMessageBox;
    if(victory) mb->setText("Congratulations! \nYou have won");
    else mb->setText("Ooops, you have lost...\n");
    QAbstractButton *quit = mb->addButton(tr("Quit"), QMessageBox::NoRole);
    mb->exec();

    //close the board and show the start window
    if(mb->clickedButton() == quit)
    {
        mb->close();
        board->close();
        start *game = new start;
        game->show();
    }
}
