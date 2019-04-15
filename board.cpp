#include "ui_mainwindow.h"
#include "board.h"
#include <cmath>
#include <QRandomGenerator>
#include <QDateTime>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QAbstractButton>
#include <QHBoxLayout>
#include "constants.h"

Board::Board(Color pl)
    :player(pl)
{
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
        }
    }
    analyseField();


    /*for(int i = 0; i < 64; ++i)
    {
      //  fields[i].coordinate = i;
        fields[i].getCheckerbutton()->indexChange(i);
        if(i < 8)
        {
            ui->layout1->addWidget(fields[i].getCheckerbutton());
            modelBoard(i);
        }
        else if(i < 16)
        {
            ui->layout2->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else if(i < 24)
        {
            ui->layout3->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else if(i < 32)
        {
            ui->layout4->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else if(i < 40)
        {
            ui->layout5->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else if(i < 48)
        {
            ui->layout6->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else if(i < 56)
        {
            ui->layout7->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        else
        {
            ui->layout8->addWidget(fields[i].checkerbutton);
            modelBoard(i);
        }
        connect(fields[i].checkerbutton, SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
    }*/
}

//check if field is black
bool Board::isBlackField(int i)
{
    if((i%2 + i/8)%2 == 0) return false;
    return true;
}

//function sets right picture
/*void Board::setPicture(int i, QString path)
{
    QPixmap checkerbuttonPix(path);
    fields[i].getCheckerbutton()->setPixmap(checkerbuttonPix);
    fields[i].getCheckerbutton()->setScaledContents(true);
}*/


//models board before the beginning of the game
void Board::modelBoard(int i)
{
     if(!isBlackField(i)) // field is white
     {
         fields[i].setPicture();
     }
     else
     {
         fields[i].setColor((Color::BLACK)); //field is black
         if(i <= 23)
         {
             //black figures
             Figure* figure = new Figure(Color::BLACK);
             fields[i].setFigure(figure);
             fields[i].setPicture();
         }
         else if(i >= 40)
         {
             //white figures
             Figure* figure = new Figure(Color::WHITE);
             fields[i].setFigure(figure);
             fields[i].setPicture();
         }
     }




         /*if(i/8 < 3)
         {
             fields[i].setPicture(blackSimpleFigure);
             fields[i].setColor(Color::BLACK);
             //setPicture(i, "Images/redSimpleFigure.png");
             //fields[i].empty = false;
             //fields[i].color = 2;
             if(i/8 == 2)
             {
                 if(i == 23)
                 {
                     fields[i].addMove(30);
                 }
                 else
                 {
                     fields[i].addMove(i+7);
                     fields[i].addMove(i+9);
                 }
                 blackMove.push_back(i);
             }
         }
         else if(i/8 > 4)
         {
             fields[i].setPicture(whiteSimpleFigure);
             //setPicture(i, "Images/whiteSimpleFigure.png");
             //fields[i].empty = false;
             fields[i].setColor(Color::BLACK);
             if(i/8 == 5)
             {
                 if(i == 40)
                 {
                     fields[i].addMove(33);
                 }
                 else
                 {
                     fields[i].addMove(i-7);
                     fields[i].addMove(i-9);
                 }
                 whiteMove.push_back(i);
             }
         }
         else
         {
             fields[i].setPicture(blackField);
              // setPicture(i, "Images/blackField.png");
         }*/
     //}
}

void Board::isClicked(int i)
{
    prevActive = active;
    active = i;
    //if plsyer`s figure was chosen and it was either first move or previous chosen field was empty
    //mark chosen field and all possible moves
    if((prevActive==-1 || !fields[prevActive].getFigure()) && player == fields[active].getColor())
    {
        markField(active);
    }
    //if players figure was chosen and previous chosen field contained opponents figure
    //mark chosen field and all possible moves
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() != player && player == fields[active].getColor())
    {
        markField(active);
    }
    //if previous figure was player`s figure
    else if(fields[prevActive].getFigure()&&fields[prevActive].getFigure()->getColor() == player)
    {
        deleteMark(active);
        //if chosen field is black and empty
        if(!fields[active].getFigure() && isBlackField(active))
        {
            //move
            //maybe
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


//check if field j is availible from the field i
bool Board::isNeighbor(int i, int j)
{
    for(int k = 0; k < fields[i].neighbors.size(); ++k)
    {
        if(fields[i].neighbors[k] == j) return true;
    }
    return false;
}

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
        return;
    }

    //do nothing if player needs to beat but this figure cannot beat
    if(whiteBeat && fields[i].getColor() == Color::WHITE || blackBeat&&fields[i].getColor()==Color::BLACK) return;

    //mark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
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
        return;
    }

    //do nothing if player needs to beat but this figure cannot beat
    if(whiteBeat && fields[i].getColor() == Color::WHITE || blackBeat&&fields[i].getColor()==Color::BLACK) return;

    //unmark all fields where figure can move
    for(int j = 0; j < fields[i].moves.size(); ++j)
    {
        fields[fields[i].moves[j]].unmarkField();
    }
}


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
}

Board::~Board()
{
}
