#include "player.h"

Player::Player(Board *b, Color c)
    :board(b), color(c)
{

}

Person::Person(Board *b, Color c)
    :Player(b, c)
{

}

Bot::Bot(Board *b, Color c)
    :Player(b, c)
{

}

void Person::changeFieldActivity()
{
    board->setActivity(true);
}

void Bot::changeFieldActivity()
{
    board->setActivity(false);
}

void Person::move()
{
    changeFieldActivity();
}

void Bot::move()
{
    changeFieldActivity();
}
