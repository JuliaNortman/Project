#pragma once
#include "board.h"
#include "mainwindow.h"
#include <QWidget>

class Board;

class Player
{
protected:
    Board *board;
    Color color;
    bool canMove = true;/*information about whether it is Player`s turn to move or not*/
public:
    Player(Color c);
    virtual ~Player() = default;
    virtual void move() = 0;
    bool getCanMove(){return canMove;}
    void setCanMove(bool canMove){this->canMove = canMove;}
    Color getColor(){return color;}
    void setBoard(Board* pBoard){board = pBoard;}
};

class  Person : public Player
{
public:
    Person(Color c);
    void move() override;
    void setBoardActive();
};

class  Bot : public Player
{
public:
    Bot( Color c);
    void move() override;
    void setBoardActive();
    void setBoardUnactive();
    void think(int&, int&);/*AI*/
};

