#include "ui_mainwindow.h"
#include "board.h"

Board::Board()
{
    fields = new field[64];
    white = black = 0;
    active = prevActive = -1;
    white = black = 12;
    mustBeatWhite = new int[3];
    mustBeatBlack = new int[3];
    for(int i = 0; i < 3; ++i)
    {
        mustBeatBlack[i] = mustBeatWhite[i] = -1;
    }

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
                     fields[i].neighbors[0] = 30;
                 }
                 else
                 {
                     fields[i].neighbors[0] = i+7;
                     fields[i].neighbors[1] = i+9;
                 }
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
                     fields[i].neighbors[0] = 33;
                 }
                 else
                 {
                     fields[i].neighbors[0] = i-7;
                     fields[i].neighbors[1] = i-9;
                 }
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
    ui->debug->insertPlainText(QString::number(i) + '\n');
    prevActive = active;
    active = i;
    if(mustBeatWhite[0] == -1)
    {
        if(prevActive == -1 && fields[i].color == 1)
        {
            markField(i);
        }
        else if(!isBlackField(prevActive) && fields[i].color == 1)
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
                    //сделать ход
                }
                else
                {
                    deleteMark(prevActive);
                }
            }
        }
    }
}


//check if field j is availible from the field i
bool Board::isNeighbor(int i, int j)
{
    for(int k = 0; k < 4; ++k)
    {
        if(fields[i].neighbors[k] == j) return true;
    }
    return false;
}

void Board::markField(int i)
{
    setPicture(i, "Images/chosenWhiteSimple.png");
    for(int j = 0; j < 4; ++j)
    {
        if(fields[i].neighbors[j] != -1)
        {
            setPicture(fields[i].neighbors[j], "Images/chosenEmptyField.png");
        }
        else break;
    }
}

void Board::deleteMark(int i)
{
    setPicture(i, "Images/whiteSimpleFigure.png");
    for(int j = 0; j < 4; ++j)
    {
        if(fields[i].neighbors[j] != -1)
        {
            setPicture(fields[i].neighbors[j], "Images/blackField.png");
        }
        else break;
    }
}

Board::~Board()
{
   // delete [] fields;
}
