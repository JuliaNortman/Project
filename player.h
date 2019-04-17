#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include <QWidget>

class Player
{
protected:
    Board *board;
    Color color;
public:
    Player(Board *b, Color c);
    virtual ~Player() = default;
    virtual void move() = 0;
    /*makes board unactive if current player is not a person
    and active if it is a person*/
    virtual void changeFieldActivity();
};

class  Person : public Player
{
private:

public:
    Person(Board *b, Color c);
    void move();
    void changeFieldActivity();
};

class  Bot : public Player
{
public:
    Bot(Board *b, Color c);
    void move();
    void changeFieldActivity();
};

#endif // PLAYER_H
