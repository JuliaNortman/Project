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
    /*makes board unactive if current player is not a person
    and active if it is a person*/
    virtual void changeFieldActivity() = 0;
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
    void changeFieldActivity() override;
};

class  Bot : public Player
{
public:
    Bot( Color c);
    void move() override;
    void changeFieldActivity() override;
};

