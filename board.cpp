#include "board.h"
#include "ui_board.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <QRandomGenerator>
#include <QDateTime>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QAbstractButton>
#include <QHBoxLayout>
#include "constants.h"


/**
 * constructor
 *
 * @param plyr Player that will start the game
*/
Board::Board(Player* plyr, QWidget *parent) :
    QDialog(parent),
    currentPlayer(plyr),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    this->player = currentPlayer->getColor();
    fields = new field[SIZE];
    whiteBeat = blackBeat = false;
    active = prevActive = -1;
    white = black = 12;


    if(player == Color::WHITE)
    {
        QHBoxLayout *layout = nullptr;
        for(int i = 0; i < SIZE; ++i)
        {
            if(i%static_cast<int>(sqrt(SIZE)) == 0)
            {
                layout  = new QHBoxLayout;
            }
            fields[i].setCoordinate(i);
            fields[i].getCheckerbutton()->indexChange(i);
            layout->addWidget(fields[i].getCheckerbutton());
            if((i+1)%static_cast<int>(sqrt(SIZE)) == 0)
            {
              ui->gridChBoard->addLayout(layout, i/static_cast<int>(sqrt(SIZE)), 0);
            }
            modelBoard(i);
            connect(fields[i].getCheckerbutton(), SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
        }
    }
    else
    {
        QHBoxLayout *layout = nullptr;
        for(int i = SIZE-1; i >= 0; --i)
        {
            if((i+1)%static_cast<int>(sqrt(SIZE)) == 0)
            {
               layout  = new QHBoxLayout;
            }
            fields[i].setCoordinate(i);
            fields[i].getCheckerbutton()->indexChange(i);
            layout->addWidget(fields[i].getCheckerbutton());
            if(i%static_cast<int>(sqrt(SIZE)) == 0)
            {
                ui->gridChBoard->addLayout(layout, (SIZE-i-1)/static_cast<int>(sqrt(SIZE)), 0);
            }
            modelBoard(i);
            connect(fields[i].getCheckerbutton(), SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
        }
    }
    correctBoard();
}

/*!
 * @brief copy constructor
 */
Board::Board(const Board& obj)
{
    white = obj.white;
    black = obj.black;
    fields = new field[SIZE];
    for(int i = 0; i < SIZE; ++i)
    {
        fields[i] = obj.fields[i];
    }
    active = obj.active;
    prevActive = obj.prevActive;
    whiteBeat = obj.whiteBeat;
    blackBeat = obj.blackBeat;
    whiteMove = obj.whiteMove;
    blackMove = obj.blackMove;
    whiteBeats = obj.whiteBeats;
    blackBeats = obj.blackBeats;
    player = obj.player;
    isActive = obj.isActive;
    currentPlayer = obj.currentPlayer;
}

/**
 * @brief checks if the field is black
 * @param i Index of the field
 * @return true if field color is black, false if white
 */
bool Board::isBlackField(int i)
{
    if((i%2 + i/static_cast<int>(sqrt(SIZE)))%2 == 0) return false;
    return true;
}

/**
 * @brief prepares board before the beginning of the game
          sets appropriate figure on the field
 * @param i Index of the field
 */
void Board::modelBoard(int i)
{
     if(isBlackField(i))
     {
         fields[i].setColor((Color::BLACK)); //field is black
         if(i < static_cast<int>(sqrt(SIZE))*3)
         {
             //black figures
             Figure* figure = new Figure(Color::BLACK);
             fields[i].setFigure(figure);
         }
         else if(i >= SIZE-static_cast<int>(sqrt(SIZE))*3)
         {
             //white figures
             Figure* figure = new Figure(Color::WHITE);
             fields[i].setFigure(figure);
         }
     }
     fields[i].setPicture();
}

/**
 * @brief Slot that is called when field is clicked on
 * @param i Index of the field that was clicked
 */
void Board::isClicked(int i)
{
    prevActive = active;
    active = i;
    //if player`s figure was chosen and it was either first move or previous chosen field was empty
    //mark chosen field and all possible moves
    if((prevActive==-1 || !fields[prevActive].getFigure()) && fields[active].getFigure()
            && player == fields[active].getFigure()->getColor())
    {
        markField(active);
    }
    //if players figure was chosen and previous chosen field contained opponents figure
    //mark chosen field and all possible moves
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() != player &&
            fields[active].getFigure() && player == fields[active].getFigure()->getColor())
    {
        markField(active);
    }
    //if previous figure was player`s figure
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() == player)
    {
        deleteMark(prevActive);
        //if chosen field is black and empty

        if(!fields[active].getFigure() && isBlackField(active) && fields[prevActive].canMoveTo(active))
        {
            //move
            move(prevActive, active);
        }
        if(fields[active].getFigure() && fields[active].getFigure()->getColor() == player)
        {
            markField(active);
        }
    }
}

/**
 * @brief Returns all the fields where a figure from the field i can move on
 * @param i Index of the field for which possible moves are counted
 *          It is guaranteed that fieled i has a figure on it
 * @return QVector<int> result of all possible moves
 */
QVector<int> Board::neighborFieldsToMove(int i)
{
    QVector<int> result;
    if(!fields[i].getFigure()) return result;
    //if target field is black and free of figures and target field index is on the checker board and
    //figure on given field is either king(can move in all directions or have certain color)
    if(i-static_cast<int>(sqrt(SIZE))-1 >= 0 && isBlackField(i-static_cast<int>(sqrt(SIZE))-1)
            && !fields[i-static_cast<int>(sqrt(SIZE))-1].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        result.push_back(i-static_cast<int>(sqrt(SIZE))-1);
    }
    if(i+static_cast<int>(sqrt(SIZE))+1 < SIZE && isBlackField(i+static_cast<int>(sqrt(SIZE))+1)
            && !fields[i+static_cast<int>(sqrt(SIZE))+1].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        result.push_back(i+static_cast<int>(sqrt(SIZE))+1);
    }
    if(i-static_cast<int>(sqrt(SIZE))+1 >= 0 && isBlackField(i-static_cast<int>(sqrt(SIZE))+1)
            && !fields[i-static_cast<int>(sqrt(SIZE))+1].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        result.push_back(i-static_cast<int>(sqrt(SIZE))+1);
    }
    if(i+static_cast<int>(sqrt(SIZE))-1 < SIZE && isBlackField(i+static_cast<int>(sqrt(SIZE))-1)
            && !fields[i+static_cast<int>(sqrt(SIZE))-1].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        result.push_back(i+static_cast<int>(sqrt(SIZE))-1);
    }
    return result;
}

/**
 * @brief Returns all the fields where a figure from the field i can beat on
 * @param i Index of the field for which possible beats are counted
 *          It is guaranteed that fieled i has a figure on it
 * @return QVector<int> result of all possible beats
 */
QVector<int> Board::neighborFieldsToBeat(int i)
{
    QVector<int> result;
    if(!fields[i].getFigure()) return result;
    //if target field and via field indexes are on the checker board
    //and target field is black and target field is free from other figures and
    //via field has figure which color differs from given field figure
    //and given figure is either king or can move in that diection
    if(i-static_cast<int>(sqrt(SIZE))-1>=0 && i-2*static_cast<int>(sqrt(SIZE))-2>=0
            && isBlackField(i-static_cast<int>(sqrt(SIZE))*2-2) && !fields[i-2*static_cast<int>(sqrt(SIZE))-2].getFigure()
            && fields[i-static_cast<int>(sqrt(SIZE))-1].getFigure()
            && fields[i].getFigure()->getColor() != fields[i-static_cast<int>(sqrt(SIZE))-1].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        result.push_back(i-2*static_cast<int>(sqrt(SIZE))-2);
    }
    if(i-static_cast<int>(sqrt(SIZE))+1>=0 && i-2*static_cast<int>(sqrt(SIZE))+2>=0
            && isBlackField(i-2*static_cast<int>(sqrt(SIZE))+2) && !fields[i-static_cast<int>(sqrt(SIZE))*2+2].getFigure()
            && fields[i-static_cast<int>(sqrt(SIZE))+1].getFigure()
            && fields[i].getFigure()->getColor() != fields[i-static_cast<int>(sqrt(SIZE))+1].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        result.push_back(i-static_cast<int>(sqrt(SIZE))*2+2);
    }
    if(i+static_cast<int>(sqrt(SIZE))+1<SIZE && i+2*static_cast<int>(sqrt(SIZE))+2<SIZE
            && isBlackField(i+2*static_cast<int>(sqrt(SIZE))+2) && !fields[i+2*static_cast<int>(sqrt(SIZE))+2].getFigure()
            && fields[i+static_cast<int>(sqrt(SIZE))+1].getFigure()
            && fields[i].getFigure()->getColor() != fields[i+static_cast<int>(sqrt(SIZE))+1].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        result.push_back(i+2*static_cast<int>(sqrt(SIZE))+2);
    }
    if(i+static_cast<int>(sqrt(SIZE))-1<SIZE && i+2*static_cast<int>(sqrt(SIZE))-2<SIZE
            && isBlackField(i+2*static_cast<int>(sqrt(SIZE))-2) && !fields[i+2*static_cast<int>(sqrt(SIZE))-2].getFigure()
            && fields[i+static_cast<int>(sqrt(SIZE))-1].getFigure()
            && fields[i].getFigure()->getColor() != fields[i+static_cast<int>(sqrt(SIZE))-1].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        result.push_back(i+2*static_cast<int>(sqrt(SIZE))-2);
    }
    return result;
}

/**
 * @brief Highlight the given field and all possible beats or moves from this field
 * @param i Field which is needed to be marked
 */
void Board::markField(int i)
{
    fields[i].markField();

    //mark all fields that this figure can beat
    if(!fields[i].beats.empty())
    {
        for(int j = 0; j < fields[i].beats.size(); ++j)
        {
            fields[fields[i].beats[j]].markField();
        }
        fields[i].moves.clear();
        return;
    }

    //do nothing if player needs to beat but this figure cannot beat
    if(whiteBeat && fields[i].getFigure()->getColor() == Color::WHITE)
    {
        fields[i].moves.clear();
        return;
    }
    if(blackBeat && fields[i].getFigure()->getColor() == Color::BLACK)
    {
        fields[i].moves.clear();
        return;
    }

    //mark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
        fields[fields[i].moves[j]].markField();
    }
}

/**
 * @brief Deletes mark from the given field and all possible beats or moves from this field
 * @param i Field to delete its mark
 */
void Board::deleteMark(int i)
{
    fields[i].unmarkField();


    //unmark all fields that this figure can beat
    if(!fields[i].beats.empty())
    {
        for(int j = 0; j < fields[i].beats.size(); ++j)
        {
            fields[fields[i].beats[j]].unmarkField();
        }
    }

    //do nothing if player needs to beat but this figure cannot beat
    if((whiteBeat && fields[i].getFigure()->getColor() == Color::WHITE)
            || (blackBeat&&fields[i].getFigure()->getColor()==Color::BLACK)) return;

    //unmark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
        fields[fields[i].moves[j]].unmarkField();
    }
}


/**
 * @brief This function is called after every change on the board
 *        It updates values for each field on the board
 */
void Board::correctBoard()
{
    whiteBeat = blackBeat = false;
    whiteMove.clear();
    blackMove.clear();
    whiteBeats.clear();
    blackBeats.clear();

    /*figure need to continue to beat
    it has possible beat moves and it`s previous move was beat
    */
    if(active != -1 && !neighborFieldsToBeat(active).empty() && fields[active].getFigure()->getBeat())
    {
        currentPlayer->setCanMove(true);/*need to move again*/
        if(fields[active].getFigure()->getColor() == Color::BLACK)
        {
            blackBeat = true;
            blackBeats.push_back(active);
        }
        else
        {
            whiteBeat = true;
            whiteBeats.push_back(active);
        }
        for(int i = 0; i < SIZE; ++i)
        {
            if(fields[i].getFigure())
            {
                fields[i].moves.clear();
                fields[i].beats.clear();
                fields[i].setBeat(false);
            }
        }
        fields[active].setBeat(true);
        fields[active].beats = neighborFieldsToBeat(active);
        fields[active].moves.clear();
        active = prevActive = -1;
        return;
    }
    active = prevActive = -1;
    /*for each field update its values*/
    for(int i = 0; i < SIZE; ++i)
    {
        fields[i].setBeat(false);
        fields[i].beats.clear();
        fields[i].moves.clear();
        if(fields[i].getFigure())
        {
            fields[i].getFigure()->setBeat(false);
            fields[i].beats = neighborFieldsToBeat(i);//sets fields that must to be beat
            if(!fields[i].beats.empty()) //if figure on this field must beat
            {
                fields[i].setBeat(true);
                if(fields[i].getFigure()->getColor() == Color::WHITE)
                {
                    whiteBeat = true;
                    whiteBeats.push_back(i);
                }
                else
                {
                    blackBeat = true;
                    blackBeats.push_back(i);
                }
            }

            fields[i].moves = neighborFieldsToMove(i);//sets all possible moves
            //if figure has possible moves
            //add figure to the possible moves on the board
            if(!fields[i].moves.empty())
            {
                if(fields[i].getFigure()->getColor() == Color::WHITE)
                {
                    whiteMove.push_back(i);
                }
                else
                {
                    blackMove.push_back(i);
                }
            }
        }
        fields[i].setPicture();
    }
    if(whiteBeat) whiteMove.clear();
    if(blackBeat) blackMove.clear();
    gameEnd();
    if(currentPlayer)currentPlayer->setCanMove(false);/*it is next player`s turn to move*/
}

/**
 * @brief Counts the index of the field that must be beaten if figure moves from field with index 'from'
 *        to the field with index 'to'
 * @param from Index of the field where figure starts its move
 * @param to Index of the field where figure ends its move
 * @return index of the field that must be beaten
 *         or -1 if it was not a beat move
 */
int Board::fieldToBeat(int from, int to)
{
    int beat = -1;
    if(to-from == -(2*static_cast<int>(sqrt(SIZE))+2)) beat = from-static_cast<int>(sqrt(SIZE))-1;
    else if(to-from == -(2*static_cast<int>(sqrt(SIZE))-2)) beat = from-static_cast<int>(sqrt(SIZE))+1;
    else if(to-from == 2*static_cast<int>(sqrt(SIZE))-2) beat = from+static_cast<int>(sqrt(SIZE))-1;
    else if(to-from == 2*static_cast<int>(sqrt(SIZE))+2) beat = from+static_cast<int>(sqrt(SIZE))+1;
    return beat;
}

/**
 * @brief Move figures from the field with index from to the field with index to
 *        and updates their pictures
 * @param from Index of the field where figure starts its move
 * @param to Index of the field where figure ends its move
 */
void Board::move(int from, int to)
{
    active = to;
    prevActive = from;
    // figure must beat
    if(fields[from].getBeat())
    {
        fields[from].getFigure()->setBeat(true);
        //calculate what field must be beaten
        int beatField = fieldToBeat(from, to);
        //decrease number of figures
        if(fields[beatField].getFigure()->getColor() == Color::BLACK)
        {
            black--;
            ui->blackNuber->setText("Black: "+QString::number(black));
        }
        else
        {
            white--;
            ui->whiteNumber->setText("White: "+QString::number(white));
        }

        delete fields[beatField].getFigure();
        fields[beatField].setFigure(nullptr);

        fields[beatField].setPicture();
    }
    else {
        fields[from].getFigure()->setBeat(false);
    }

    fields[to].setFigure(fields[from].getFigure());
    fields[from].setFigure(nullptr);
    /*set figure to be a king if it reached the line*/
    if(fields[to].getFigure() && ((fields[to].getFigure()->getColor() == Color::BLACK && to/static_cast<int>(sqrt(SIZE)) == static_cast<int>(sqrt(SIZE))-1)
            ||(fields[to].getFigure()->getColor() == Color::WHITE && to/static_cast<int>(sqrt(SIZE)) == 0)))
    {
        fields[to].getFigure()->becomeKing();
    }
    fields[from].setPicture();
    fields[to].setPicture();
    correctBoard();
    /*emit signal to inform that another player can move*/
    if(!currentPlayer->isBot())emit(moved(currentPlayer));
}


/**
 * @brief Opposite to the function move()
 *        removes the figure from the field with index to and puts it on the field with index from
 * @param from Index of the field where figure starts its move
 * @param to Index of the field where figure ends its move
 * @param wasKing Is true if the figure on the field with index to was a king before this move
 * @param king True if the figure on the field with index to is a king
 * @param hadBeat True if during the previous move figure had to beat
 */
void Board::undoMove(int from, int to, bool wasKing, bool king, bool hadBeat)
{
    active = to;
    prevActive = from;
    int beatField = fieldToBeat(from, to);
    if(beatField != -1)
    {
        Figure *figure = nullptr;
        if(fields[to].getFigure()->getColor() == Color::WHITE)
        {
            black++;
            ui->blackNuber->setText("Black: "+QString::number(black));
            figure = new Figure(Color::BLACK);
        }
        else
        {
            white++;
            ui->whiteNumber->setText("White: "+QString::number(white));
            figure = new Figure(Color::WHITE);
        }
        figure->setKing(king);
        figure->setBeat(false);
        fields[beatField].setFigure(figure);
        fields[beatField].setPicture();
    }


    //wasKing - переменная которая показывает была ли фигура которая сейчас стоит на поле to ранее дамкой,
    //если же была то при отмене хода она и должна остаться дамкой
    /*set figure to be a king if it reached the line*/
    if(fields[to].getFigure() && ((fields[to].getFigure()->getColor() == Color::BLACK && to/static_cast<int>(sqrt(SIZE)) == static_cast<int>(sqrt(SIZE))-1)
            ||(fields[to].getFigure()->getColor() == Color::WHITE && to/static_cast<int>(sqrt(SIZE)) == 0)) && !wasKing)
    {
        fields[to].getFigure()->removeKing();
    }
    fields[from].setFigure(fields[to].getFigure());
    fields[to].setFigure(nullptr);
    fields[from].getFigure()->setBeat(hadBeat);
    fields[from].setPicture();
    fields[to].setPicture();
    active = from;
    correctBoard();
}

/**
 * @brief Sets if the fields will react on the mouse click
 * @param active True if fields should react on the mouse click
 */
void Board::setActivity(bool active)
{
    isActive = active;
    for(int i = 0; i < SIZE; ++i)
    {
        fields[i].setActive(active);
    }
}

void Board::gameEnd(/*Color color*/)
{
    Color color = currentPlayer->getColor();
    /*returns true if there is no possible moves for that color*/
    if(color == Color::BLACK)
    {
        if(whiteMove.empty() && whiteBeats.empty()) emit end();//return true;
    }
    else
    {
        if(blackMove.empty() && blackBeats.empty()) emit end(); //return true;
    }
    //return false;
}

int Board::evaluateBoard(Color maximizer)
{
    int score = 0;
    for(int i = 0; i < SIZE; ++i)
    {
        /*evaluating a score based on the field itself*/
        if(!fields[i].getFigure()) score += 0;
        else if(fields[i].getFigure()->getColor() == maximizer && fields[i].getFigure()->isKing())
        {
            score += 20;
        }
        else if(fields[i].getFigure()->getColor() != maximizer && fields[i].getFigure()->isKing())
        {
            score += -20;
        }
        else if(fields[i].getFigure()->getColor() == maximizer)
        {
            score += 10;
        }
        else if(fields[i].getFigure()->getColor() != maximizer)
        {
            score += -10;
        }
        /*evaluating a score based on the figures position*/
        if(i % static_cast<int>(sqrt(SIZE)) == 0
                ||i % static_cast<int>(sqrt(SIZE)) == static_cast<int>(sqrt(SIZE))-1
                || i < static_cast<int>(sqrt(SIZE))
                || i >= SIZE-static_cast<int>(sqrt(SIZE)))
        {
            if(fields[i].getFigure() && fields[i].getFigure()->getColor() == maximizer)
            {
                score += 4;
            }
            else if(fields[i].getFigure() && fields[i].getFigure()->getColor() != maximizer)
            {
                score += -4;
            }
        }
    }
    /*there are no possible moves*/
    if(maximizer == Color::WHITE && whiteMove.empty() && whiteBeats.empty() && currentPlayer->getColor()==maximizer)
    {
        score += -100;
    }
    else if(maximizer == Color::BLACK && whiteMove.empty() && whiteBeats.empty() && currentPlayer->getColor() != maximizer)
    {
        score += 100;
    }
    else if(maximizer == Color::WHITE && blackMove.empty() && blackBeats.empty() && currentPlayer->getColor()!=maximizer)
    {
        score += 100;
    }
    else if(maximizer == Color::BLACK && blackMove.empty() && blackBeats.empty() && currentPlayer->getColor()==maximizer)
    {
        score += -100;
    }
    /*pieces that are threatened by current player*/
    if(maximizer == Color::BLACK)
    {
        int beats = 0;
        for(int j = 0; j < blackBeats.size(); ++j)
        {
            beats += fields[blackBeats[j]].beats.size();
        }
        score += 10*beats;
        beats = 0;
        for(int j = 0; j < whiteBeats.size(); ++j)
        {
            beats += fields[whiteBeats[j]].beats.size();
        }
        score += -10*beats;
    }
    else
    {
        int beats = 0;
        for(int j = 0; j < whiteBeats.size(); ++j)
        {
            beats += fields[whiteBeats[j]].beats.size();
        }
        score += 10*beats;
        beats = 0;
        for(int j = 0; j < blackBeats.size(); ++j)
        {
            beats += fields[blackBeats[j]].beats.size();
        }
        score += -10*beats;
    }
    //ui->debug->append("Evaluation score: " + QString::number(score) + '\n');
    return score;
}



field* Board::getBoardFields()
{
    field* f = new field[SIZE];
    for(int i = 0; i < SIZE; ++i)
    {
        //qDebug(std::to_string(i).c_str());
        f[i] = fields[i];
    }
    return f;
}

void Board::setBoardFields(field *f)
{
    if(fields != f)
    {
        qDebug("before delete fields in setBoard fields");
        for(int i = 0; i < SIZE; ++i)
        {
            if(fields[i].getColor()==Color::BLACK)qDebug("Color black");
            else qDebug("Color white");
        }
        //delete [] fields;
        qDebug("after delete fields in setBoard fields");
        fields = f;
        for(int i = 0; i < SIZE; ++i)
        {
            connect(fields[i].getCheckerbutton(), SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
        }
    }
}

Board::~Board()
{
    delete [] fields;
}
