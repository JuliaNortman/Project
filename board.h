#pragma once


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVector>
#include "field.h"
#include "player.h"
#include "constants.h"

class Player;

class Board :public field
{
    Q_OBJECT
public:
    Board(Player* player);
    ~Board();
    void modelBoard(int);
    //void setPicture(int, QString);
    bool isBlackField(int);
    bool isNeighbor(int, int);
    void markField(int); //???????? ????? ?????? ? ?? ???????
    void deleteMark(int); //?????? ????????? ? ????? ?????? ? ?? ???????
    void analyseField();
    bool needToBeatThisField(int, int);
    bool canMove(int, int);
    //void analyseKingField(bool&, int, QVector<int>&); //function that is used in analyseField for kings
    //void analyseSimpleField(bool&, int, int, QVector<int>&);
    void move(int, int);

    //finds all fields where the figure from field i can move
    QVector<int> neighborFieldsToMove(int);
    //finds all fields that the figure must beat
    QVector<int> neighborFieldsToBeat(int);
    //sets correct neighbors to the all fields on the board
    void correctBoard();
    void setActivity(bool);
    void setCurrentPlayer(Player* pl){currentPlayer = pl;}/*sets current player who is active at the moment*/
    bool gameEnd(Color color);/*returns true if the game is over*/

    QVector<int> getWhiteMove(){return whiteMove;}
    QVector<int> getBlackMove(){return blackMove;}
    QVector<int> getWhiteBeat(){return whiteBeats;}
    QVector<int> getBlackBeat(){return blackBeats;}
    QVector<int> getFieldBeats(int i){return fields[i].beats;}
    QVector<int> getFieldsMoves(int i){return fields[i].moves;}

protected:
    int white; //quantaty of available white figures on the field
    int black; //quantaty of available black figures on the field
    field *fields;
    int active = -1; //index of field that is active at the present moment
    int prevActive = -1;
    bool whiteBeat; //checks whether is needed to beat white figure
    bool blackBeat; //checks whether is needed to beat black figure
    QVector<int> whiteMove; //all white possible moves
    QVector<int> blackMove; //all black possible moves
    QVector<int> whiteBeats; //all fields (white figures) that need to beat
    QVector<int> blackBeats; //all fields (black figures) that need to beat
    Color player; //what color of figures main player plays
    bool isActive = true;

    Player* currentPlayer = nullptr;/*who is active at present moment*/

public slots:
    void isClicked(int i);
signals:
    void moved(Player*);/*emits when player has moved*/
};

