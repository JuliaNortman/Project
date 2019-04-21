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

void Person::setBoardActive()
{
    board->setActivity(true);
}

void Bot::setBoardActive()
{
    board->setActivity(true);
}

void Bot::setBoardUnactive()
{
    board->setActivity(false);
}

void Person::move()
{
    qDebug("before person move");
    setBoardActive();
    qDebug("Person move end");
}

void Bot::think(int& from, int& to)
{
    QVector<int> beat, move;
    if(color == Color::WHITE)
    {
        beat = board->getWhiteBeat();
        move = board->getWhiteMove();
    }
    else
    {
        beat = board->getBlackBeat();
        move = board->getBlackMove();
    }
    if(!beat.empty())
    {
        from = rand()%beat.size() - 1;
    }
    else if(!move.empty())
    {
        from = rand()%move.size() - 1;
    }
    else return;
    if(from != -1)
    {
        beat = board->getFieldBeats(from);
        move = board->getFieldsMoves(from);
        if(!beat.empty())
        {
            to = rand()%beat.size() - 1;
        }
        else if(!move.empty())
        {
            to = rand()%move.size() - 1;
        }
        else return;
    }
}

void Bot::move()
{
    qDebug("before bot move");
    setBoardUnactive();
    int from = -1, to = -1;
    think(from, to);
    if(from != -1 && to != -1)
    {
        board->move(from, to);
    }
    setBoardActive();
    qDebug("Bot move");
}
