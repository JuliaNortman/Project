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
    //qDebug("before person move");
    setBoardActive();
    //qDebug("Person move end");
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
    if(depth == DEPTH)
    {
        //qDebug("deapth");
        return score;}
    if(board->getWhiteNumber() == 0 || board->getBlackNumber() == 0)
    {
        //qDebug("No figures");
        return score;}
    if(board->getWhiteBeat().empty() && board->getWhiteMove().empty() && maximizer && color == Color::WHITE)
    {
        //qDebug("1");
        return score;}
    if(board->getBlackBeat().empty() && board->getBlackMove().empty() && maximizer && color == Color::BLACK)
    {
        //qDebug("2");
        return score;}
    if(board->getWhiteBeat().empty() && board->getWhiteMove().empty() && !maximizer && color == Color::BLACK)
    {
        //qDebug("3");
        return score;}
    if(board->getBlackBeat().empty() && board->getBlackMove().empty() && !maximizer && color == Color::WHITE)
    {
        //qDebug("4");
        return score;}
    QVector<int> kings = board->getKings();
    //bool wasKing = false;
    if(maximizer)
    {
        //qDebug("MAXIMIZER");
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
            //wasKing = board->isKing(from, kings);
            toMoves = board->getFieldBeats(from);
            if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
            for(int j = 0; j < toMoves.size(); ++j)
            {
                to = toMoves[j];
                bool king = false;
                bool hadBeat = false;
                int beatfield = board->fieldToBeat(from, to);
                hadBeat = board->getField(from).getFigure()->getBeat();
                if(beatfield != -1)
                {
                    king = board->getField(beatfield).getFigure()->isKing();
                }
               // qDebug("FROM/TO: ");
                //qDebug(std::to_string(from).c_str());
                //qDebug(std::to_string(to).c_str());
                //qDebug("before maximizer move");
                bool wasKing = false;
                wasKing = board->getField(from).getFigure()->isKing();
                //if(wasKing) board->setText(QString::number(from)+" wasKing\n");
                //else board->setText(QString::number(from)+" was not king\n");
                QVector<int> Kings = board->getKings();
                board->move(from, to, true);
                //qDebug("after max move");
                //Board* b = new Board(*board);
                best = max(best, minimax(board, depth+1, !maximizer));
                //qDebug("before undo move in max");
                //if(b)delete b;
                board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
                //qDebug("after undo move in max");
                board->correctBoard();
                //qDebug("after correct board in max");
                //qDebug("end maximizer");

            }
        }
        //qDebug("BEST");
        //qDebug(std::to_string(best).c_str());
        return best;
    }
    else
    {
        int best = INT_MAX;
        //qDebug("MINIMIZER");
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
            //wasKing = board->isKing(from, kings);
            toMoves = board->getFieldBeats(from);
            if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
            for(int j = 0; j < toMoves.size(); ++j)
            {
                to = toMoves[j];
                bool king = false;
                bool hadBeat = false;
                int beatfield = board->fieldToBeat(from, to);
                hadBeat = board->getField(from).getFigure()->getBeat();
                if(beatfield != -1)
                {
                    king = board->getField(beatfield).getFigure()->isKing();
                }
                //qDebug("FROM/TO: ");
               //// qDebug(std::to_string(from).c_str());
               // qDebug(std::to_string(to).c_str());
                //qDebug("before min move");
                bool wasKing = false;
                wasKing = board->getField(from).getFigure()->isKing();
                //if(wasKing) board->setText(QString::number(from)+"wasKing\n");
                //else board->setText(QString::number(from)+"was not king\n");
                QVector<int> Kings = board->getKings();
                board->move(from, to, true);
                //qDebug("after min move");
                //Board*b = new Board(*board);
                best = min(best, minimax(board, depth+1, maximizer));
                //qDebug("before undo move in min");
                //if(b)delete b;
                board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
                //qDebug("after undo move in min");
                board->correctBoard(true);
                //qDebug("after correct board in min");
                //qDebug("end minimizer");
            }
        }
        //qDebug("BEST");
        //qDebug(std::to_string(best).c_str());
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
    QVector<int> kings = board->getKings();
    bool wasKing = false;
    for (int i = 0; i < fromMoves.size(); ++i)
    {
        from = fromMoves[i];
        //wasKing = board->isKing(from, kings);
        //board->setText("WASKING FIRST  "+QString::number(from)+" "+QString::number(wasKing)+'\n');
        toMoves = board->getFieldBeats(from);
        if(toMoves.empty()) toMoves = board->getFieldsMoves(from);
        for(int j = 0; j < toMoves.size(); ++j)
        {
            to = toMoves[j];
            bool king = false;
            int beatfield = board->fieldToBeat(from, to);
            bool hadBeat = false;
            hadBeat = board->getField(from).getFigure()->getBeat();
            if(beatfield != -1)
            {
                king = board->getField(beatfield).getFigure()->isKing();
            }
            /*qDebug("FROM/TO: ");
            qDebug(std::to_string(from).c_str());
            qDebug(std::to_string(to).c_str());
            qDebug("Before move in hard think");*/
            bool wasKing = false;
            wasKing = board->getField(from).getFigure()->isKing();
            /*if(wasKing) board->setText(QString::number(from)+"wasKing\n");
            else board->setText(QString::number(from)+"was not king\n");*/
            //board->setText("WASKING SECOND  "+QString::number(from)+" "+QString::number(wasKing)+'\n');
            QVector<int> Kings = board->getKings();
            board->move(from, to, true);
            //Board* b = new Board(*board);
            //qDebug("after move in hard think");
            int moveVal = minimax(board, 0, false);
            //qDebug("before undo in hard think");
            //if(b)delete b;
            //board->setText("WASKING THIRD  "+QString::number(from)+" "+QString::number(wasKing)+'\n');
            board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
            //qDebug("after undo in hard think");
            board->correctBoard(true);

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
    //qDebug("before bot move");
    setBoardUnactive();
    while(canMove)
    {
        QTime time;
        time.start();
        for(;time.elapsed() < 300;) {
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
   // qDebug("End bot move");
}
