#include "ui_mainwindow.h"
#include "board.h"
#include <cmath>
#include<QRandomGenerator>
#include <QDateTime>

Board::Board()
{
    fields = new field[64];
    whiteBeat = blackBeat = false;
    active = prevActive = -1;
    white = black = 12;
    /*mustBeatWhite = new int[3];
    mustBeatBlack = new int[3];
    for(int i = 0; i < 3; ++i)
    {
        mustBeatBlack[i] = mustBeatWhite[i] = -1;
    }*/

    for(int i = 0; i < 64; ++i)
    {
        fields[i].coord = i;
        fields[i].checkerbutton->indexChange(i);
        if(i < 8)
        {
            ui->layout1->addWidget(fields[i].checkerbutton);
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
    }
}

//check if field is black
bool Board::isBlackField(int i)
{
    if((i%2 + i/8)%2 == 0) return false;
    return true;
}

//function sets right picture
void Board::setPicture(int i, QString path)
{
    QPixmap checkerbuttonPix(path);
    fields[i].checkerbutton->setPixmap(checkerbuttonPix);
    fields[i].checkerbutton->setScaledContents(true);
}

void Board::modelBoard(int i)
{
     if((i%2 + i/8)%2 == 0)
     {
         setPicture(i, "Images/whiteField.png");
     }
     else
     {
         if(i/8 < 3)
         {
             setPicture(i, "Images/redSimpleFigure.png");
             fields[i].empty = false;
             fields[i].color = 2;
             if(i/8 == 2)
             {
                 if(i == 23)
                 {
                     fields[i].neighbors.push_back(30);
                 }
                 else
                 {
                     fields[i].neighbors.push_back(i+7);
                     fields[i].neighbors.push_back(i+9);
                 }
                 blackMove.push_back(i);
             }
         }
         else if(i/8 > 4)
         {
             setPicture(i, "Images/whiteSimpleFigure.png");
             fields[i].empty = false;
             fields[i].color = 1;
             if(i/8 == 5)
             {
                 if(i == 40)
                 {
                     fields[i].neighbors.push_back(33);
                 }
                 else
                 {
                     fields[i].neighbors.push_back(i-7);
                     fields[i].neighbors.push_back(i-9);
                 }
                 whiteMove.push_back(i);
             }
         }
         else
         {
             setPicture(i, "Images/blackField.png");
         }
     }
}

void Board::isClicked(int i)
{
    ui->debug->append("Click");
    /*if(prevActive!=-1)
    {
        fields[33].neighbors.push_back(24);
        fields[33].neighbors.push_back(26);
    }*/
    ui->debug->insertPlainText(QString::number(i) + '\n');
    prevActive = active;
    active = i;

        if(prevActive == -1 && fields[i].color == 1)
        {
            //ui->analyseDebug->append("a");
            markField(i);
        }
        else if(!isBlackField(prevActive) && fields[i].color == 1)
        {
           // ui->analyseDebug->append("b");
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==0 && fields[i].color == 1)
        {
            //ui->analyseDebug->append("c");
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==2 && fields[i].color == 1)
        {
            //ui->analyseDebug->append("d");
            markField(i);
        }
        else if(isBlackField(prevActive) && fields[prevActive].color==1)
        {
            //ui->analyseDebug->append("e");
            if(!isBlackField(i) || fields[i].color == 2)
            {
                //ui->analyseDebug->append("g");
                deleteMark(prevActive);
            }
            else if(fields[i].color == 1)
            {
               // ui->analyseDebug->append("h");
                deleteMark(prevActive);
                markField(i);
            }
            else if(fields[i].color == 0)
            {
               // ui->analyseDebug->append("i");
                if(isNeighbor(prevActive, i))
                {
                   // ui->analyseDebug->append("j");
                    for(int j = 0; j < fields[prevActive].neighbors.size(); ++j)
                    {
                        setPicture(fields[prevActive].neighbors[j], "Images/blackField.png");
                    }
                    move(prevActive, i);
                    analyseField();

                    for(int k = 0; k < blackMove.size(); ++k)
                    {
                        //ui->analyseDebug->append("BlackMove: " + QString::number(blackMove[k]));
                    }
                    for(int k = 0; k < whiteMove.size(); ++k)
                    {
                       // ui->analyseDebug->append("WhiteMove: " + QString::number(whiteMove[k]));
                    }
                    ui->analyseDebug->append("MustWhiteBeat: " + QString::number(whiteBeat));
                    ui->analyseDebug->append("MustBlackBeat: " + QString::number(blackBeat));

                    if(!whiteBeat || !fields[i].needToBeat)
                    {
                        //black move
                        srand(QDateTime::currentMSecsSinceEpoch());
                        int from = 0 + rand()%(blackMove.size()-1);
                        int to = 0 + rand()%(fields[from].neighbors.size()-1);
                        move(blackMove[from], fields[blackMove[from]].neighbors[to]);
                        analyseField();

                        for(int k = 0; k < blackMove.size(); ++k)
                        {
                            ui->analyseDebug->append("BlackMove: " + QString::number(blackMove[k]));
                        }
                        for(int k = 0; k < whiteMove.size(); ++k)
                        {
                            ui->analyseDebug->append("WhiteMove: " + QString::number(whiteMove[k]));
                        }

                        ui->analyseDebug->append("MustWhiteBeat: " + QString::number(whiteBeat));
                        ui->analyseDebug->append("MustBlackBeat: " + QString::number(blackBeat));


                    }
                }
                else
                {
                    deleteMark(prevActive);
                }
            }
        }
       /* for(int l = 0; l < 64; ++l)
        {
            connect(fields[l].checkerbutton, SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
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
    setPicture(i, "Images/chosenWhiteSimple.png");
    for(int j = 0; j < fields[i].neighbors.size(); ++j)
    {
        setPicture(fields[i].neighbors[j], "Images/chosenEmptyField.png");
    }
}

void Board::deleteMark(int i)
{
    setPicture(i, "Images/whiteSimpleFigure.png");
    for(int j = 0; j < fields[i].neighbors.size(); ++j)
    {
        setPicture(fields[i].neighbors[j], "Images/blackField.png");

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
                        fields[ind].neighbors.empty();
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



/*void Board::analyseSimpleField(bool &fieldBeat, int i, int sign, QVector<int>&fieldMove)
{
    int arr[8] = {i+7, i+9, i-7, i-9, i+14, i+18, i-18, i-14};
    if(!fieldBeat)
    {
        for(int j = sign; j < 2+sign; ++j)
        {
            if(canMove(i, arr[j]))
            {
                fieldMove.push_back(i);
                fields[i].neighbors.push_back(arr[j]);
            }
        }
    }
    for(int j = sign + 4; j < sign + 6; ++j)
    {
        if(needToBeatThisField(i, arr[j]))
        {
            if(!fieldBeat)
            {
                fieldBeat = true;
                while(!fieldMove.empty())
                {
                    fields[fieldMove.last()].neighbors.empty();
                    fieldMove.pop_back();
                }
            }
            if(fieldMove.empty() || fieldMove.last()!=i)
            {
                fieldMove.push_back(i);
            }
            fields[i].neighbors.push_back(arr[j]);
            fields[i].needToBeat = true;
        }
    }
}*/


void Board::analyseSimpleField(bool &fieldBeat, int i, int sign, QVector<int> &fieldMove )
{

    /*ui->analyseDebug->append("Color: " + QString::number(fields[i].color));
    ui->analyseDebug->append("Coord: "+QString::number(fields[i].coord));
    ui->analyseDebug->append("Empty: "+QString::number(fields[i].empty));
    ui->analyseDebug->append("King: "+QString::number(fields[i].king));
    ui->analyseDebug->append("NeedToBeat: "+QString::number(fields[i].needToBeat));
    for(int s = 0; s < fields[i].neighbors.size(); ++s)
    {
        ui->analyseDebug->append("Neighbors: "+QString::number(fields[i].neighbors[s]));
    }
    ui->analyseDebug->append("\n***\n");*/


    int arr[8] = {i+7, i+9, i-7, i-9, i+14, i+18, i-18, i-14};
    if(fieldBeat)
    {
        for(int j = 4+sign; j < 6+sign; ++j)
        {
            //ui->analyseDebug->append("field beat");
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
            //ui->analyseDebug->append("not field beat 1");
            if(needToBeatThisField(i, arr[j]))
            {
                if(!fieldBeat)
                {
                    fieldBeat = true;
                    while(!fieldMove.empty())
                    {
                       // ui->analyseDebug->append("empty fieldMove");
                        int ind = fieldMove.last();
                        fieldMove.pop_back();
                        fields[ind].neighbors.empty();
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
           // ui->analyseDebug->append(QString::number(i) + ": right loop");
            for(int j = sign; j < 2+sign; ++j)
            {
                //ui->analyseDebug->append("not field beat 2");
                //ui->analyseDebug->append("Bool can move: " + QString::number(canMove(i, arr[j])));
              //  ui->analyseDebug->append("Bool can move: ");
                if(canMove(i, arr[j]))
                {
                    //ui->analyseDebug->append("Can move");
                    fields[i].neighbors.push_back(arr[j]);
                    if(fieldMove.empty() || fieldMove.last() != i)
                    {
                        //ui->analyseDebug->append("push_back");
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
        //ui->analyseDebug->append(QString::number(i));
        fields[i].needToBeat = false;
        fields[i].neighbors.clear();
        if(isBlackField(i) && fields[i].king && fields[i].color == 2)
        {
           // ui->analyseDebug->insertPlainText("BlackFieldKing");
            analyseKingField(blackBeat, i, blackMove);
        }
        else if(isBlackField(i) && fields[i].king && fields[i].color == 1)
        {
           // ui->analyseDebug->insertPlainText("WhiteFieldKing");
            analyseKingField(whiteBeat, i, whiteMove);
        }
        else if(isBlackField(i) && fields[i].color == 2)
        {
           // ui->analyseDebug->insertPlainText("BlackFieldSimple");
            analyseSimpleField(blackBeat, i, 0, blackMove);
        }
        else if(isBlackField(i) && fields[i].color == 1)
        {
           // ui->analyseDebug->insertPlainText("WhiteFieldSimple");
            analyseSimpleField(whiteBeat, i, 2, whiteMove);
        }




        ui->analyseDebug->append("Color: " + QString::number(fields[i].color));
        ui->analyseDebug->append("Coord: "+QString::number(fields[i].coord));
        ui->analyseDebug->append("Empty: "+QString::number(fields[i].empty));
        ui->analyseDebug->append("King: "+QString::number(fields[i].king));
        ui->analyseDebug->append("NeedToBeat: "+QString::number(fields[i].needToBeat));
        for(int s = 0; s < fields[i].neighbors.size(); ++s)
        {
            ui->analyseDebug->append("Neighbors: "+QString::number(fields[i].neighbors[s]));
        }
        ui->analyseDebug->append("\n***\n");

    }
    if(white == 0)
    {
        ui->debug->append("You have lost:(");
    }
    if(black == 0)
    {
        ui->debug->append("You have won!");
    }






}

void Board::move(int from, int to)
{
    fields[to].king = fields[from].king;
    fields[to].empty = false;
    if(fields[from].color == 2)
    {
        if(to/8 == 7)
        {
            setPicture(to, "Images/redKingFigure.png");
            fields[to].king = true;
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
        else
        {
            setPicture(to, "Images/whiteSimpleFigure.png");
        }
        fields[to].color = 1;
        fields[to].needToBeat = false;
    }
    if(abs(from-to)==14 || abs(from-to)==18)
    {
        if(fields[to].color == 2) white--;
        else black--;
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
       // ui->analyseDebug->insertPlainText("1");
        return false;
    }
    if(!fields[j].empty)
    {
       // ui->analyseDebug->insertPlainText("2");
        return false;
    }
     //ui->analyseDebug->insertPlainText("3");
    return  true;
}

Board::~Board()
{
   // delete [] fields;
}
