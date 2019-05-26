#include "player.h"
#include <stdlib.h>
#include <ctime>

Player::Player(Color c)
    :color(c) {}

Person::Person(Color c)
    :Player(c) {}

Bot::Bot(Color c)
    :Player(c) {}

/**
 * @brief allow board to react on clicks
 */
void Person::setBoardActive()
{
    board->setActivity(true);
}

/**
 * @brief allow board to react on fields
 */
void Bot::setBoardActive()
{
    board->setActivity(true);
}

/**
 * @brief forbid board to react on fields
 */
void Bot::setBoardUnactive()
{
    board->setActivity(false);
}


void Person::move()
{
    setBoardActive();
}

/**
 * @brief artificial intelligence
 * randomly choose where to move
 * @return structure Move
 */
Move Bot::easythink()
{
    Move moves;
    int from = -1, to = -1;
    srand(static_cast<unsigned int>(time(nullptr)));
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
        int i = rand()%beat.size();
        if(i != 0) i--;
        from = beat[i];
    }
    else if(!move.empty())
    {
        int i = rand()%move.size();
        if(i != 0) i--;
        from = move[i];
    }
    if(from != -1)
    {
        beat = board->getFieldBeats(from);
        move = board->getFieldsMoves(from);
        if(!beat.empty())
        {
            int i = rand()%beat.size();
            if(i != 0) i--;
            to = beat[i];
        }
        else if(!move.empty())
        {
            int i = rand()%move.size();
            if(i != 0) i--;
            to = move[i];
        }
    }
    moves.from = from;
    moves.to = to;
    return moves;
}

/*int Bot::minimax(Board *board, int depth, bool maximizer)
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
    //QVector<int> kings = board->getKings();
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
                /*bool king = false;
                bool hadBeat = false;
                int beatfield = board->fieldToBeat(from, to);
                hadBeat = board->getField(from).getFigure()->getBeat();
                if(beatfield != -1)
                {
                    king = board->getField(beatfield).getFigure()->isKing();
                }*/
               // qDebug("FROM/TO: ");
                //qDebug(std::to_string(from).c_str());
                //qDebug(std::to_string(to).c_str());
                //qDebug("before maximizer move");
                /*bool wasKing = false;
                wasKing = board->getField(from).getFigure()->isKing();*/
                //if(wasKing) board->setText(QString::number(from)+" wasKing\n");
                //else board->setText(QString::number(from)+" was not king\n");
                //QVector<int> Kings = board->getKings();*/
                /*field* fields = board->getBoardFields();
                //board->move(from, to, true);
                //qDebug("after max move");
                //Board* b = new Board(*board);
                best = max(best, minimax(board, depth+1, !maximizer));
                //qDebug("before undo move in max");
                //if(b)delete b;
                //board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
                //qDebug("after undo move in max");
                board->setBoardFields(fields);
                board->setActivePrevactive(from, to);
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
                /*bool king = false;
                bool hadBeat = false;
                int beatfield = board->fieldToBeat(from, to);
                hadBeat = board->getField(from).getFigure()->getBeat();
                if(beatfield != -1)
                {
                    king = board->getField(beatfield).getFigure()->isKing();
                }*/
                //qDebug("FROM/TO: ");
               // qDebug(std::to_string(from).c_str());
               // qDebug(std::to_string(to).c_str());
                //qDebug("before min move");
                //bool wasKing = false;
                //wasKing = board->getField(from).getFigure()->isKing();
                //if(wasKing) board->setText(QString::number(from)+"wasKing\n");
                //else board->setText(QString::number(from)+"was not king\n");
                //QVector<int> Kings = board->getKings();*/
                /*field* fields = board->getBoardFields();
                board->move(from, to);
                //qDebug("after min move");
                //Board*b = new Board(*board);
                best = min(best, minimax(board, depth+1, maximizer));
                //qDebug("before undo move in min");
                //if(b)delete b;
                //board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
                //qDebug("after undo move in min");
                board->setBoardFields(fields);
                board->setActivePrevactive(from, to);
                board->correctBoard();
                //qDebug("after correct board in min");
                //qDebug("end minimizer");
            }
        }
        //qDebug("BEST");
        //qDebug(std::to_string(best).c_str());
        return best;
    }
}*/

/*Move Bot::hardThink()
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
    //QVector<int> kings = board->getKings();
    //bool wasKing = false;
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
            //bool king = false;
            //int beatfield = board->fieldToBeat(from, to);
            //bool hadBeat = false;
            //hadBeat = board->getField(from).getFigure()->getBeat();
            /*if(beatfield != -1)
            {
                king = board->getField(beatfield).getFigure()->isKing();
            }*/
            /*qDebug("FROM/TO: ");
            qDebug(std::to_string(from).c_str());
            qDebug(std::to_string(to).c_str());
            qDebug("Before move in hard think");*/
            /*bool wasKing = false;
            wasKing = board->getField(from).getFigure()->isKing();*/
            /*if(wasKing) board->setText(QString::number(from)+"wasKing\n");
            else board->setText(QString::number(from)+"was not king\n");*/
            //board->setText("WASKING SECOND  "+QString::number(from)+" "+QString::number(wasKing)+'\n');
            //QVector<int> Kings = board->getKings();*/
           /* qDebug("before get Board fields in hard think");
            field *fields = board->getBoardFields();
            qDebug("after get Board fields in hard think");
            board->move(from, to);
            //Board* b = new Board(*board);
            qDebug("after move in hard think");
            int moveVal = minimax(board, 0, false);
            qDebug("before setBoardFields in hard think");
            //if(b)delete b;
            //board->setText("WASKING THIRD  "+QString::number(from)+" "+QString::number(wasKing)+'\n');
            //board->undoMove(from, to, wasKing, Kings, king, hadBeat, true);
            //qDebug("after undo in hard think");
            board->setBoardFields(fields);
            //qDebug("after setBoardFields in hard think");
            board->setActivePrevactive(from, to);
            //qDebug("before correct in hard think");
            board->correctBoard();
            board->setActivity(true);

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
*/

/**
 * @brief move
 */
void Bot::move()
{
    setBoardUnactive(); //forbid board to rect on clicks
    while(canMove)
    {
        /*wait*/
        QTime time;
        time.start();
        for(;time.elapsed() < 700;) {
            QApplication::processEvents(nullptr);
        }
        int from = -1, to = -1;
        Move move = easythink();
        from = move.from;
        to = move.to;
        if(from != -1 && to != -1)
        {
            board->setActivePrevactive(from, to);
            board->move(from, to);
        }
    }

    setBoardActive();//allow board to react on clicks
    emit(board->moved(this));
}
