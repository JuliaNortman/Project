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


/*constructor
*Player* plyr - pointer to the player that will start the game
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

/*copy constructor*/
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

//check if field is black
bool Board::isBlackField(int i)
{
    if((i%2 + i/static_cast<int>(sqrt(SIZE)))%2 == 0) return false;
    return true;
}

//models board before the beginning of the game
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

/*
*slot that is called when the field was clicked on
* i - index of the clicked field
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
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() != player &&fields[active].getFigure() && player == fields[active].getFigure()->getColor())
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

/*
* returns vector of field`s indexes where figure can move on
* i - index of the current figure`s position
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

/*
* returns vector of field`s indexes where figure can beat on
* i - index of the current figure`s position
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

/*
*marks all fields where figure can move on
* i - index of the field`s index
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


/*
*delete mark from all fields that where marked by markField() function
* i - index of the field`s index
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
    if((whiteBeat && fields[i].getFigure()->getColor() == Color::WHITE) || (blackBeat&&fields[i].getFigure()->getColor()==Color::BLACK)) return;

    //unmark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
        fields[fields[i].moves[j]].unmarkField();
    }
}

void Board::correctBoard()
{
    whiteBeat = blackBeat = false;
    //qDebug("before white move clear");
    whiteMove.clear();
    blackMove.clear();
    whiteBeats.clear();
    blackBeats.clear();

    //qDebug("after clear");
    /*figure need to continue to beat
    *it has possible beat moves and it`s previous move was beat
    */
    //qDebug("Active/ prevactive");
    //qDebug(std::to_string(active).c_str());
    //qDebug(std::to_string(prevActive).c_str());
    /*if(active != -1&&!neighborFieldsToBeat(active).empty()) qDebug("not empty");
    else qDebug("empty");*/
    /*if(active!=-1&&fields[active].getFigure()->getBeat())qDebug("getBeat");*/
    if(/*active != -1 &&*/ !neighborFieldsToBeat(active).empty() && fields[active].getFigure()->getBeat())
    {
        //qDebug("Continue beat");
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
    //qDebug("before active");
    active = prevActive = -1;
    //qDebug("after active");
    for(int i = 0; i < SIZE; ++i)
    {
        //qDebug(std::to_string(i).c_str());
        fields[i].setBeat(false);
        fields[i].beats.clear();
        fields[i].moves.clear();
        if(fields[i].getFigure())
        {
            fields[i].getFigure()->setBeat(false);
            fields[i].beats = neighborFieldsToBeat(i);//sets fields that must to be beat
            //qDebug("beats size: ");
            //qDebug(std::to_string(fields[i].beats.size()).c_str());
            if(!fields[i].beats.empty()) //if figure on this field must beat
            {
                fields[i].setBeat(true);
                //qDebug("field[i] beats size");
                //qDebug(std::to_string(fields[i].beats.size()).c_str());
                if(fields[i].getFigure()->getColor() == Color::WHITE)
                {
                    whiteBeat = true;
                    //qDebug("push back white to beat");
                    whiteBeats.push_back(i);
                }
                else
                {
                    blackBeat = true;
                    //qDebug("push back black to beat");
                    blackBeats.push_back(i);
                }
            }

            fields[i].moves = neighborFieldsToMove(i);//sets all possible moves
            //qDebug("moves size: ");
            //qDebug(std::to_string(fields[i].moves.size()).c_str());
            //if figure has possible moves
            //add figure to the possible moves on the board
            if(!fields[i].moves.empty())
            {
                if(fields[i].getFigure()->getColor() == Color::WHITE)
                {
                    //qDebug("push back white to move");
                    whiteMove.push_back(i);
                }
                else
                {
                    //qDebug("push back black to move");
                    blackMove.push_back(i);
                }
            }
            /*qDebug("end for loop");
            qDebug("Total white/blak beats size");
            qDebug(std::to_string(whiteBeats.size()).c_str());
            qDebug(std::to_string(blackBeats.size()).c_str());*/

        }
        fields[i].setPicture();
    }
    if(whiteBeat) whiteMove.clear();
    if(blackBeat) blackMove.clear();
    //if(whiteBeat) qDebug("whiteBeat");
    //if(blackBeat) qDebug("blackBeat");
    //qDebug("before setCanMove");
    //if(gameEnd(currentPlayer->getColor())) ui->debug->append("END\n");
    gameEnd();
    /*if(!AI)*/ if(currentPlayer)currentPlayer->setCanMove(false);/*it is next player`s turn to move*/
    //qDebug("End correct");
}

int Board::fieldToBeat(int from, int to)
{
    int beat = -1;
    if(to-from == -(2*static_cast<int>(sqrt(SIZE))+2)) beat = from-static_cast<int>(sqrt(SIZE))-1;
    else if(to-from == -(2*static_cast<int>(sqrt(SIZE))-2)) beat = from-static_cast<int>(sqrt(SIZE))+1;
    else if(to-from == 2*static_cast<int>(sqrt(SIZE))-2) beat = from+static_cast<int>(sqrt(SIZE))-1;
    else if(to-from == 2*static_cast<int>(sqrt(SIZE))+2) beat = from+static_cast<int>(sqrt(SIZE))+1;
    return beat;
}

void Board::move(int from, int to, bool AI)
{
    active = to;
    prevActive = from;
    //qDebug("start move");
    // figure must beat
    if(fields[from].getBeat())
    {
        //qDebug("must beat");
        fields[from].getFigure()->setBeat(true);
        //calculate what field must be beaten
        int beatField = fieldToBeat(from, to);
        //decrease number of figures
        if(fields[beatField].getFigure()->getColor() == Color::BLACK)
        {
            black--;
            if(!AI)ui->blackNuber->setText("Black: "+QString::number(black));
        }
        else
        {
            white--;
            if(!AI)ui->whiteNumber->setText("White: "+QString::number(white));
        }

        delete fields[beatField].getFigure();
        fields[beatField].setFigure(nullptr);

        if(!AI)fields[beatField].setPicture();
    }
    else {
        fields[from].getFigure()->setBeat(false);
    }


    //qDebug("set figure");
    fields[to].setFigure(fields[from].getFigure());
    //qDebug("remove figure");
    fields[from].setFigure(nullptr);
    /*set figure to be a king if it reached the line*/
    if(fields[to].getFigure() && ((fields[to].getFigure()->getColor() == Color::BLACK && to/static_cast<int>(sqrt(SIZE)) == static_cast<int>(sqrt(SIZE))-1)
            ||(fields[to].getFigure()->getColor() == Color::WHITE && to/static_cast<int>(sqrt(SIZE)) == 0)))
    {
        //qDebug("becomes king");
        fields[to].getFigure()->becomeKing();
    }
    //qDebug("set picture from");
    if(!AI){
        fields[from].setPicture();
        //qDebug("set picture to");
        fields[to].setPicture();
    }
    //qDebug("end Move");
    correctBoard();
    //qDebug("after correct board in move");
    /*emit signal to inform that another player can move*/
    if(!AI)emit(moved(currentPlayer));
}

void Board::undoMove(int from, int to, bool wasKing, QVector<int> Kings, bool king, bool hadBeat, bool AI)
{
    //qDebug("start undo move");
    active = to;
    prevActive = from;
    //qDebug("from");
    //qDebug(std::to_string(from).c_str());
    //qDebug("to");
    //qDebug(std::to_string(to).c_str());
    int beatField = fieldToBeat(from, to);
    if(beatField != -1)
    {
        qDebug("beat field");
        //qDebug(std::to_string(beatField).c_str());
        Figure *figure = nullptr;
        if(fields[to].getFigure()->getColor() == Color::WHITE)
        {
            //qDebug("undo black figure");
            black++;
            ui->blackNuber->setText("Black: "+QString::number(black));
            figure = new Figure(Color::BLACK);
        }
        else
        {
            //qDebug("undo white figure");
            white++;
            ui->whiteNumber->setText("White: "+QString::number(white));
            figure = new Figure(Color::WHITE);
        }
        figure->setKing(king);
        figure->setBeat(false);
        fields[beatField].setFigure(figure);
        if(!AI)fields[beatField].setPicture();

        /*figure->setKing(wasKing);
        if(isKing(beatField, Kings)) figure->setKing(true);
        fields[beatField].setFigure(figure);
        if(!AI)fields[beatField].setPicture();
        fields[beatField].getFigure()->setBeat(false);*/
    }


    //wasKing - переменная которая показывает была ли фигура которая сейчас стоит на поле to ранее дамкой,
    //если же была то при отмене хода она и должна остаться дамкой
    /*set figure to be a king if it reached the line*/
    if(fields[to].getFigure() && ((fields[to].getFigure()->getColor() == Color::BLACK && to/static_cast<int>(sqrt(SIZE)) == static_cast<int>(sqrt(SIZE))-1)
            ||(fields[to].getFigure()->getColor() == Color::WHITE && to/static_cast<int>(sqrt(SIZE)) == 0)) && !wasKing)
    {
        //ui->debug->append("REMOVES KING");
        fields[to].getFigure()->removeKing();
    }
    //qDebug("set figure");
    fields[from].setFigure(fields[to].getFigure());
    //qDebug("remove figure");
    fields[to].setFigure(nullptr);
    //qDebug("undo before set beat");
    fields[from].getFigure()->setBeat(hadBeat);

    if(!AI)
    {
        //qDebug("set picture from");
        fields[from].setPicture();
        //qDebug("set picture to");
        fields[to].setPicture();
    }
    active = from;
    //qDebug("end undo Move");
    //correctBoard();
}

/*
//analyse for king
void Board::analyseKingField(bool &fieldBeat, int i, QVector<int> &fieldMove)
{
    int arr[8] = {i+7, i-7, i+9, i-9, i+18, i-18, i+14, i-14};
    if(fieldBeat)
    {
        for(int j = 4; j < 8; ++j)
        {
            if(needToBeatThisField(i, arr[j]))
            {
                fields[i].needToBeat = true;
                fields[i].neighbors.push_back(arr[j]);
                if(fieldMove.empty() || fieldMove.last() != i)
                {
                    fieldMove.push_back(i);
                }
            }
        }
    }
    else
    {
        for(int j = 4; j < 8; ++j)
        {
            if(needToBeatThisField(i, arr[j]))
            {
                if(!fieldBeat)
                {
                    fieldBeat = true;
                    while(!fieldMove.empty())
                    {
                        int ind = fieldMove.last();
                        fieldMove.pop_back();
                        fields[ind].neighbors.clear();
                    }
                    fields[i].needToBeat = true;
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
                else
                {
                    fields[i].needToBeat = true;
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
            }
        }
        if(!fieldBeat)
        {
            for(int j = 0; j < 4; ++j)
            {
                if(canMove(i, arr[j]))
                {
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
            }
        }
    }
}


//sign == 0 --- black field
//sign == 2 --- white field
void Board::analyseSimpleField(bool &fieldBeat, int i, int sign, QVector<int> &fieldMove )
{
    int arr[8] = {i+7, i+9, i-7, i-9, i+14, i+18, i-18, i-14};
    if(fieldBeat)
    {
        for(int j = 4+sign; j < 6+sign; ++j)
        {
            if(needToBeatThisField(i, arr[j]))
            {
                fields[i].needToBeat = true;
                fields[i].neighbors.push_back(arr[j]);
                if(fieldMove.empty() || fieldMove.last() != i)
                {
                    fieldMove.push_back(i);
                }
            }
        }
    }
    else
    {
        for(int j = 4+sign; j < 6+sign; ++j)
        {
            if(needToBeatThisField(i, arr[j]))
            {
                if(!fieldBeat)
                {
                    fieldBeat = true;
                    while(!fieldMove.empty())
                    {
                        int ind = fieldMove.last();
                        fieldMove.pop_back();
                        fields[ind].neighbors.clear();
                    }
                    fields[i].needToBeat = true;
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
                else
                {
                    fields[i].needToBeat = true;
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
            }
        }
        if(!fieldBeat)
        {
            for(int j = sign; j < 2+sign; ++j)
            {
                if(canMove(i, arr[j]))
                {
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        fieldMove.push_back(i);
                    }
                }
            }
        }
    }
}

void Board::analyseField()
{
    whiteMove.clear();
    blackMove.clear();
    whiteBeat = false;
    blackBeat = false;
    for(int i = 0; i < 64; ++i)
    {
        fields[i].needToBeat = false;
        fields[i].neighbors.clear();
        if(isBlackField(i) && fields[i].king && fields[i].color == 2)
        {
            analyseKingField(blackBeat, i, blackMove);
        }
        else if(isBlackField(i) && fields[i].king && fields[i].color == 1)
        {
            analyseKingField(whiteBeat, i, whiteMove);
        }
        else if(isBlackField(i) && fields[i].color == 2)
        {
            analyseSimpleField(blackBeat, i, 0, blackMove);
        }
        else if(isBlackField(i) && fields[i].color == 1)
        {
            analyseSimpleField(whiteBeat, i, 2, whiteMove);
        }

    }
    if(white == 0 || whiteMove.empty())
    {
        QMessageBox *lost = new QMessageBox;
        lost->setText("Ooops, you have lost...\n");
        QAbstractButton *restart = lost->addButton(tr("Restart"), QMessageBox::YesRole);
        QAbstractButton *quit = lost->addButton(tr("Quit"), QMessageBox::NoRole);
        lost->exec();
        if(lost->clickedButton() == restart)
        {
            white = black = 12;
            active = prevActive = -1;
            whiteBeat = blackBeat = false;
            whiteMove.clear();
            blackMove.clear();
            for(int i = 0; i < 64; ++i)
            {
                fields[i].beat = false;
                fields[i].color = 0;
                fields[i].empty = true;
                fields[i].king = false;
                fields[i].needToBeat = false;
                fields[i].neighbors.clear();
                modelBoard(i);
                lost->close();
            }
        }
        else if(lost->clickedButton() == quit)
        {
            lost->close();
            this->close();
        }
    }
    if(black == 0 || blackMove.empty())
    {
        QMessageBox *lost = new QMessageBox;
        lost->setText("Congratulation!!! You have won!\n");
        QAbstractButton *restart = lost->addButton(tr("Restart"), QMessageBox::YesRole);
        QAbstractButton *quit = lost->addButton(tr("Quit"), QMessageBox::NoRole);
        lost->exec();
        if(lost->clickedButton() == restart)
        {
            white = black = 12;
            active = prevActive = -1;
            whiteBeat = blackBeat = false;
            whiteMove.clear();
            blackMove.clear();
            for(int i = 0; i < 64; ++i)
            {
                fields[i].beat = false;
                fields[i].color = 0;
                fields[i].empty = true;
                fields[i].king = false;
                fields[i].needToBeat = false;
                fields[i].neighbors.clear();
                modelBoard(i);
                lost->close();
            }
        }
        else if(lost->clickedButton() == quit)
        {
            lost->close();
            this->close();
        }
    }
}

void Board::move(int from, int to)
{
    if(abs(from-to)==14 || abs(from-to)==18)
    {
        fields[to].beat = true;
    }
    fields[from].beat = false;
    fields[to].king = fields[from].king;
    fields[to].empty = false;
    if(fields[from].color == 2)
    {
        if(to/8 == 7)
        {
            setPicture(to, "Images/redKingFigure.png");
            fields[to].king = true;
        }
        else if(fields[from].king)
        {
            setPicture(to, "Images/redKingFigure.png");
        }
        else
        {
            setPicture(to, "Images/redSimpleFigure.png");
        }
        fields[to].color = 2;
        fields[to].needToBeat = false;
    }
    else
    {
        if(to/8 == 0)
        {
            setPicture(to, "Images/whiteKingFigure.png");
            fields[to].king = true;
        }
        else if(fields[from].king)
        {
            setPicture(to, "Images/whiteKingFigure.png");
        }
        else
        {
            setPicture(to, "Images/whiteSimpleFigure.png");
        }
        fields[to].color = 1;
        fields[to].needToBeat = false;
    }
    if(abs(from-to)==14 || abs(from-to)==18)
    {
        if(fields[to].color == 2)
        {
            white--;
            ui->whiteNumber->setText("White: " + QString::number(white));
        }
        else
        {
            black--;
            ui->blackNuber->setText("Black: " + QString::number(black));
        }
        if(from - to == 14)
        {
            setPicture(from-7, "Images/blackField.png");
            fields[from-7].color = 0;
            fields[from-7].empty = true;
            fields[from-7].king = false;
            fields[from-7].needToBeat = false;
            fields[from-7].neighbors.clear();
        }
        else if(from - to == -14)
        {
            setPicture(from+7, "Images/blackField.png");
            fields[from+7].color = 0;
            fields[from+7].empty = true;
            fields[from+7].king = false;
            fields[from+7].needToBeat = false;
            fields[from+7].neighbors.clear();
        }
        else if(from - to == 18)
        {
            setPicture(from-9, "Images/blackField.png");
            fields[from-9].color = 0;
            fields[from-9].empty = true;
            fields[from-9].king = false;
            fields[from-9].needToBeat = false;
            fields[from-9].neighbors.clear();
        }
        else if(from - to == -18)
        {
            setPicture(from+9, "Images/blackField.png");
            fields[from+9].color = 0;
            fields[from+9].empty = true;
            fields[from+9].king = false;
            fields[from+9].needToBeat = false;
            fields[from+9].neighbors.clear();
        }
    }
    fields[from].color = 0;
    fields[from].empty = true;
    fields[from].king = false;
    fields[from].needToBeat = false;
    fields[from].neighbors.clear();
    setPicture(from, "Images/blackField.png");
}

bool Board::needToBeatThisField(int i, int j)
{
    if(j < 0 || j > 64 || !isBlackField(j)) return false;
    if(!fields[j].empty) return  false;
    if((i+18==j)&&fields[i+9].color!=0 &&fields[i+9].color!=fields[i].color)
    {
        return true;
    }
    if((i+14==j)&&fields[i+7].color!=0 &&fields[i+7].color!=fields[i].color)
    {
        return true;
    }
    if((i-18==j)&&fields[i-9].color!=0 &&fields[i-9].color!=fields[i].color)
    {
        return true;
    }
    if((i-14==j)&&fields[i-7].color!=0 &&fields[i-7].color!=fields[i].color)
    {
        return true;
    }
    return false;
}

bool Board::canMove(int i, int j)
{
    if(j < 0 || j > 64 || !isBlackField(j))
    {
        return false;
    }
    if(!fields[j].empty)
    {
        return false;
    }
    return  true;
}*/

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
