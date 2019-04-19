#include "player.h"

Player::Player(Color c)
    :color(c)
{

}

Person::Person(Color c)
    :Player(c)
{

}

Bot::Bot(Color c)
    :Player(c)
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
    qDebug("Person move");
}

void Bot::move()
{
    changeFieldActivity();
    qDebug("Bot move");
}
