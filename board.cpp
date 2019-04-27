#include "ui_mainwindow.h"
#include "board.h"
#include <cmath>
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

Board::Board(Player* plyr)
    :currentPlayer(plyr)
{
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
            if(i%8 == 0)
            {
               layout  = new QHBoxLayout;
            }
            fields[i].setCoordinate(i);
            fields[i].getCheckerbutton()->indexChange(i);
            layout->addWidget(fields[i].getCheckerbutton());
            if((i+1)%8 == 0)
            {
                ui->gridChBoard->addLayout(layout, i/8, 0);
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
            if((i+1)%8 == 0)
            {
               layout  = new QHBoxLayout;
            }
            fields[i].setCoordinate(i);
            fields[i].getCheckerbutton()->indexChange(i);
            layout->addWidget(fields[i].getCheckerbutton());
            if(i%8 == 0)
            {
                ui->gridChBoard->addLayout(layout, (SIZE-i-1)/8, 0);
            }
            modelBoard(i);
            connect(fields[i].getCheckerbutton(), SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
        }
    }
    correctBoard();
}

//check if field is black
bool Board::isBlackField(int i)
{
    if((i%2 + i/8)%2 == 0) return false;
    return true;
}

//models board before the beginning of the game
void Board::modelBoard(int i)
{
     if(isBlackField(i))
     {
         fields[i].setColor((Color::BLACK)); //field is black
         if(i <= 23)
         {
             //black figures
             Figure* figure = new Figure(Color::BLACK);
             fields[i].setFigure(figure);
         }
         else if(i >= 40)
         {
             //white figures
             Figure* figure = new Figure(Color::WHITE);
             fields[i].setFigure(figure);
         }
     }
     fields[i].setPicture();
}

bool Board::canMove(int i)
{
    if(fields[i].getColor() == Color::BLACK)
    {

    }
    else
    {

    }
    return true;
}

void Board::isClicked(int i)
{
    ui->debug->append(QString::number(i)+'\n');
    prevActive = active;
    active = i;
    /*qDebug("Active: PrevActive: ");
    qDebug(std::to_string(active).c_str());
    qDebug(std::to_string(prevActive).c_str());*/
    //if player`s figure was chosen and it was either first move or previous chosen field was empty
    //mark chosen field and all possible moves
    if((prevActive==-1 || !fields[prevActive].getFigure()) && fields[active].getFigure()
            && player == fields[active].getFigure()->getColor())
    {
        //ui->debug->append("Mark field1");
        markField(active);
    }
    //if players figure was chosen and previous chosen field contained opponents figure
    //mark chosen field and all possible moves
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() != player &&fields[active].getFigure() && player == fields[active].getFigure()->getColor())
    {
        //ui->debug->append("Mark field2");
        markField(active);
    }
    //if previous figure was player`s figure
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() == player)
    {
        //ui->debug->append("Delete mark1");
        deleteMark(prevActive);
        //if chosen field is black and empty
        /*if(fields[prevActive].canMoveTo(active, whiteBeat, blackBeat, currentPlayer->getColor()))
        {
            ui->debug->append("true");
        }
        else
        {
            ui->debug->append("false");
        }*/
        if(!fields[active].getFigure() && isBlackField(active) &&
                fields[prevActive].canMoveTo(active, whiteBeat, blackBeat, currentPlayer->getColor()) && canMove(active))
        {
            //move
            qDebug("move");
            move(prevActive, active);
        }
        if(fields[active].getFigure() && fields[active].getFigure()->getColor() == player)
        {
           // ui->debug->append("Mark field3");
            markField(active);
        }
    }
        /*if(prevActive == -1 && fields[i].getFigure()->getColor() == Color::BLACK)
        {
            markField(i);
        }
        else if(!isBlackField(prevActive) && fields[i].getFigure()->getColor()== Color::BLACK)
        {
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==0 && fields[i].color == 1)
        {
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==2 && fields[i].color == 1)
        {
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==1)
        {
            if(!isBlackField(i) || fields[i].color == 2)
            {
                deleteMark(prevActive);
            }
            else if(fields[i].color == 1)
            {
                deleteMark(prevActive);
                markField(i);
            }
            else if(fields[i].color == 0)
            {
                if(isNeighbor(prevActive, i))
                {
                    for(int j = 0; j < fields[prevActive].neighbors.size(); ++j)
                    {
                        setPicture(fields[prevActive].neighbors[j], "Images/blackField.png");
                    }
                    move(prevActive, i);
                    analyseField();
                    if(black > 0 && (!fields[i].beat || !fields[i].needToBeat) && prevActive != -1)
                    {
                        //black move
                        srand(QDateTime::currentMSecsSinceEpoch());
                        int from = 0;
                        if(blackMove.size()-1==0) from = 0;
                        else from = 0 + rand()%(blackMove.size()-1);
                        int to = 0;
                        if(fields[from].neighbors.size()-1 == 0) to = 0;
                        else to = 0 + rand()%(fields[from].neighbors.size()-1);
                        if(blackBeat && fields[blackMove[from]].needToBeat)
                        {
                            int fromField = blackMove[from];
                            int toField = fields[blackMove[from]].neighbors[to];
                            while(fields[fromField].needToBeat)
                            {
                                QTime time;
                                time.start();
                                for(;time.elapsed() < 500;) {
                                    qApp->processEvents(nullptr);
                                }
                                move(fromField, toField);
                                analyseField();
                                fromField = toField;
                                toField = fields[fromField].neighbors[0];
                            }
                        }
                        else
                        {
                            QTime time;
                            time.start();
                            for(;time.elapsed() < 500;) {
                                qApp->processEvents(nullptr);
                            }
                            move(blackMove[from], fields[blackMove[from]].neighbors[to]);
                            analyseField();
                        }
                    }
                }
                else
                {
                    deleteMark(prevActive);
                }
                for(int p = 0; p < 64; ++p) fields[p].beat = false;
            }
        }*/
}

QVector<int> Board::neighborFieldsToMove(int i)
{
    QVector<int> result;
    //if target field is black and free of figures and target field index is on the checker board and
    //figure on given field is either king(can move in all directions or have certain color)
    if(i-9 >= 0 && isBlackField(i-9) && !fields[i-9].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        //qDebug("i-9");
        result.push_back(i-9);
    }
    if(i+9 < SIZE && isBlackField(i+9) && !fields[i+9].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        //qDebug("i+9");
        result.push_back(i+9);
    }
    if(i-7 >= 0 && isBlackField(i-7) && !fields[i-7].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        //qDebug("i-7");
        result.push_back(i-7);
    }
    if(i+7 < SIZE && isBlackField(i+7) && !fields[i+7].getFigure()
            &&(fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        //qDebug("i+7");
        result.push_back(i+7);
    }
    //qDebug("result size");
    //qDebug(std::to_string(result.size()).c_str());
    return result;
}

QVector<int> Board::neighborFieldsToBeat(int i)
{
    QVector<int> result;

    //if target field and via field indexes are on the checker board
    //and target field is black and target field is free from other figures and
    //via field has figure which color differs from given field figure
    //and given figure is either king or can move in that diection
    if(i-9>=0 && i-18>=0 && isBlackField(i-18) && !fields[i-18].getFigure()
            && fields[i-9].getFigure()
            && fields[i].getFigure()->getColor() != fields[i-9].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        //qDebug("i-18");
        result.push_back(i-18);
    }
    if(i-7>=0 && i-14>=0 && isBlackField(i-14) && !fields[i-14].getFigure()
            && fields[i-7].getFigure()
            && fields[i].getFigure()->getColor() != fields[i-7].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::WHITE))
    {
        //qDebug("i-14");
        result.push_back(i-14);
    }
    if(i+9<SIZE && i+18<SIZE && isBlackField(i+18) && !fields[i+18].getFigure()
            && fields[i+9].getFigure()
            && fields[i].getFigure()->getColor() != fields[i+9].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        //qDebug("i+18");
        result.push_back(i+18);
    }
    if(i+7<SIZE && i+14<SIZE && isBlackField(i+14) && !fields[i+14].getFigure()
            && fields[i+7].getFigure()
            && fields[i].getFigure()->getColor() != fields[i+7].getFigure()->getColor()
            && (fields[i].getFigure()->isKing()||fields[i].getFigure()->getColor() == Color::BLACK))
    {
        //qDebug("i+14");
        result.push_back(i+14);
    }
    return result;
}
/*
//check if field j is availible from the field i
bool Board::isNeighbor(int i, int j)
{
    for(int k = 0; k < fields[i].neighbors.size(); ++k)
    {
        if(fields[i].neighbors[k] == j) return true;
    }
    return false;
}
*/

void Board::markField(int i)
{
    fields[i].markField();

    //mark all fields that this figure can beat
    if(!fields[i].beats.empty())
    {
        //qDebug("first if");
        for(int j = 0; j < fields[i].beats.size(); ++j)
        {
            fields[fields[i].beats[j]].markField();
        }
        fields[i].moves.clear();
        return;
    }

    //do nothing if player needs to beat but this figure cannot beat
    //if(whiteBeat) qDebug("whiteBeat");
    //if(fields[i].getFigure()->getColor() == Color::WHITE) qDebug("WHITE");
    //if(blackBeat) qDebug("blackBeat");
    //if(fields[i].getFigure()->getColor() == Color::BLACK) qDebug("BLACK");
    if(whiteBeat && fields[i].getFigure()->getColor() == Color::WHITE)
    {
        //qDebug("second if");
        fields[i].moves.clear();
        return;
    }
    if(blackBeat && fields[i].getFigure()->getColor() == Color::BLACK)
    {
        //qDebug("third if");
        fields[i].moves.clear();
        return;
    }

    //mark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
        //qDebug("fourth if");
        fields[fields[i].moves[j]].markField();
    }
}

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
    //qDebug("start correct");
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
    if(!neighborFieldsToBeat(active).empty() && fields[active].getFigure()->getBeat())
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
            //qDebug("end for loop");
            //qDebug("Total white/blak beats size");
            //qDebug(std::to_string(whiteBeats.size()).c_str());
            //qDebug(std::to_string(blackBeats.size()).c_str());

        }
    }
    if(whiteBeat) whiteMove.clear();
    if(blackBeat) blackMove.clear();
    if(whiteBeat) qDebug("whiteBeat");
    if(blackBeat) qDebug("blackBeat");
    //qDebug("before setCanMove");
    if(currentPlayer)currentPlayer->setCanMove(false);/*it is next player`s turn to move*/
    //qDebug("End correct");
}

void Board::move(int from, int to)
{
    //qDebug("start move");
    // figure must beat
    if(fields[from].getBeat())
    {
        //qDebug("must beat");
        fields[from].getFigure()->setBeat(true);
        int beatField = 0;
        //calculate what field must be beaten
        if(to-from == -18) beatField = from-9;
        else if(to-from == -14) beatField = from-7;
        else if(to-from == 14) beatField = from+7;
        else if(to-from == 18) beatField = from+9;
        //decrease number of figures
        if(fields[beatField].getFigure()->getColor() == Color::BLACK)
        {
            black--;
            ui->blackNuber->setText(std::to_string(black).c_str());
        }
        else
        {
            white--;
            ui->whiteNumber->setText(std::to_string(white).c_str());
        }

        delete fields[beatField].getFigure();
        fields[beatField].setFigure(nullptr);

        fields[beatField].setPicture();
    }
    else {
        fields[from].getFigure()->setBeat(false);
    }


    //qDebug("set figure");
    fields[to].setFigure(fields[from].getFigure());
    //qDebug("remove figure");
    fields[from].setFigure(nullptr);
    /*set figure to be a king if it reached the line*/
    if(fields[to].getFigure() && ((fields[to].getFigure()->getColor() == Color::BLACK && to/8 == 7)
            ||(fields[to].getFigure()->getColor() == Color::WHITE && to/8 == 0)))
    {
        //qDebug("becomes king");
        fields[to].getFigure()->becomeKing();
    }
    //qDebug("set picture from");
    fields[from].setPicture();
    //qDebug("set picture to");
    fields[to].setPicture();
    //qDebug("end Move");
    correctBoard();
    /*emit signal to inform that another player can move*/
    emit(moved(currentPlayer));
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

bool Board::gameEnd(Color color)
{
    /*returns true if there is no possible moves for that color*/
    if(color == Color::BLACK)
    {
        if(whiteMove.empty() && whiteBeats.empty()) return true;
    }
    else
    {
        if(blackMove.empty() && blackBeats.empty()) return true;
    }
    return false;
}

Board::~Board()
{
    delete [] fields;
}

