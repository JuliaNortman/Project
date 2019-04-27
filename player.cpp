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
        //qDebug("color white");
        beat = board->getWhiteBeat();
        move = board->getWhiteMove();
    }
    else
    {
        //qDebug("color black");
        beat = board->getBlackBeat();
        move = board->getBlackMove();
    }
    //qDebug("beat size: move size:");
    //qDebug(std::to_string(beat.size()).c_str());
    //qDebug(std::to_string(move.size()).c_str());
    if(!beat.empty())
    {
        int i = rand()%beat.size();
        if(i != 0) i--;
        //qDebug(std::to_string(i).c_str());
        //qDebug(std::to_string(beat[i]).c_str());
        from = beat[i];
        //qDebug("from beat");
    }
    else if(!move.empty())
    {
        int i = rand()%move.size();
        if(i != 0) i--;
        from = move[i];
        //qDebug("from move");
    }
    if(from != -1)
    {
        beat = board->getFieldBeats(from);
        move = board->getFieldsMoves(from);
        /*qDebug("move/beat size:");
        qDebug(std::to_string(beat.size()).c_str());
        qDebug(std::to_string(move.size()).c_str());*/
        if(!beat.empty())
        {
            int i = rand()%beat.size();
            if(i != 0) i--;
            to = beat[i];
            //qDebug("to beat");
        }
        else if(!move.empty())
        {
            int i = rand()%move.size();
            if(i != 0) i--;
            to = move[i];
            //qDebug("to Move");
        }
    }
    /*qDebug("From: To:");
    qDebug(std::to_string(from).c_str());
    qDebug(std::to_string(to).c_str());*/
}

void Bot::move()
{
    qDebug("before bot move");
    setBoardUnactive();
    while(canMove)
    {
        QTime time;
        time.start();
        for(;time.elapsed() < 1500;) {
            QApplication::processEvents(nullptr);
        }
        //qDebug("while");
        int from = -1, to = -1;
        think(from, to);
        if(from != -1 && to != -1)
        {
            //qDebug("real bot move");
            board->setActivePrevactive(from, to);
            board->move(from, to);
        }
        //break;
    }

    setBoardActive();
    //qDebug("End bot move");
}
