#include "player.h"
#include <stdlib.h>

int max(int a, int b)
{
    if(a >= b) return a;
    return b;
}

int min(int a, int b)
{
    if(a <= b) return a;
    return b;
}

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

void Bot::easythink(int& from, int& to)
{
    srand(static_cast<unsigned int>(time(nullptr)));
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

int Bot::minimax(Board *board, int depth, bool maximizer)
{
    int score = board->evaluateBoard(color);
    if(depth == DEPTH) return score;
    if(board->getWhiteNumber() == 0 || board->getBlackNumber() == 0) return score;
    if(board->getWhiteBeat().empty() && board->getWhiteMove().empty() && maximizer && color == Color::WHITE) return score;
    if(board->getBlackBeat().empty() && board->getBlackMove().empty() && maximizer && color == Color::BLACK) return score;
    if(board->getWhiteBeat().empty() && board->getWhiteMove().empty() && !maximizer && color == Color::BLACK) return score;
    if(board->getBlackBeat().empty() && board->getBlackMove().empty() && !maximizer && color == Color::WHITE) return score;

    if(maximizer)
    {
        int best = INT_MIN;
        QVector<int> fromMoves, toMoves;
        if(color == Color::BLACK)
        {
            fromMoves = board->getBlackBeat();
            if(fromMoves.empty()) fromMoves = board->getBlackMove();
        }
        else
        {
            fromMoves = board->getWhiteBeat();
            if(fromMoves.empty()) fromMoves = board->getWhiteMove();
        }
        int from = -1, to = -1;
        for (int i = 0; i < fromMoves.size(); ++i)
        {
            from = fromMoves[i];
            toMoves = board->getFieldBeats(from);
            if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
            for(int j = 0; j < toMoves.size(); ++j)
            {
                to = toMoves[j];
                bool king = false;
                int beatfield = board->fieldToBeat(from, to);
                if(beatfield != -1) king = board->getField(beatfield).getFigure()->isKing();

                board->move(from, to);
                best = max(best, minimax(board, depth+1, !maximizer));
                if(king) board->undoMove(from, to, king);
                else board->undoMove(from, to);
                board->correctBoard();

            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        QVector<int> fromMoves, toMoves;
        if(color == Color::WHITE)
        {
            fromMoves = board->getBlackBeat();
            if(fromMoves.empty()) fromMoves = board->getBlackMove();
        }
        else
        {
            fromMoves = board->getWhiteBeat();
            if(fromMoves.empty()) fromMoves = board->getWhiteMove();
        }
        int from = -1, to = -1;
        for (int i = 0; i < fromMoves.size(); ++i)
        {
            from = fromMoves[i];
            toMoves = board->getFieldBeats(from);
            if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
            for(int j = 0; j < toMoves.size(); ++j)
            {
                to = toMoves[j];
                bool king = false;
                int beatfield = board->fieldToBeat(from, to);
                if(beatfield != -1) king = board->getField(beatfield).getFigure()->isKing();

                board->move(from, to);
                best = min(best, minimax(board, depth+1, !maximizer));
                if(king) board->undoMove(from, to, king);
                else board->undoMove(from, to);
                board->correctBoard();

            }
        }
        return best;
    }
}

Move Bot::hardThink()
{
    int bestVal = INT_MIN;
    int from = -1, to = -1;
    Move bestMove;
    bestMove.from = bestMove.to = -1;
    QVector<int> fromMoves, toMoves;
    if(color == Color::BLACK)
    {
        fromMoves = board->getBlackBeat();
        if(fromMoves.empty()) fromMoves = board->getBlackMove();
    }
    else
    {
        fromMoves = board->getWhiteBeat();
        if(fromMoves.empty()) fromMoves = board->getWhiteMove();
    }
    for (int i = 0; i < fromMoves.size(); ++i)
    {
        from = fromMoves[i];
        toMoves = board->getFieldBeats(from);
        if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
        for(int j = 0; j < toMoves.size(); ++j)
        {
            to = toMoves[j];
            bool king = false;
            int beatfield = board->fieldToBeat(from, to);
            if(beatfield != -1) king = board->getField(beatfield).getFigure()->isKing();

            board->move(from, to);
            int moveVal = minimax(board, 0, true);
            if(king) board->undoMove(from, to, king);
            else board->undoMove(from, to);
            board->correctBoard();

            if(moveVal > bestVal)
            {
                bestMove.from = from;
                bestMove.to = to;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

void Bot::move()
{
    qDebug("before bot move");
    setBoardUnactive();
    while(canMove)
    {
        QTime time;
        time.start();
        for(;time.elapsed() < 800;) {
            QApplication::processEvents(nullptr);
        }
        //qDebug("while");
        int from = -1, to = -1;
        Move move = hardThink();
        from = move.from;
        to = move.to;
        if(from != -1 && to != -1)
        {
            //qDebug("real bot move");
            board->setActivePrevactive(from, to);
            board->move(from, to);
        }
        //break;
    }

    setBoardActive();
    qDebug("End bot move");
}
