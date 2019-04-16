#ifndef BOARD_H
#define BOARD_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVector>
#include "field.h"
#include "constants.h"

class Board :public field
{
    Q_OBJECT
public:
    Board(Color pl);
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
    void analyseKingField(bool&, int, QVector<int>&); //function that is used in analyseField for kings
    void analyseSimpleField(bool&, int, int, QVector<int>&);
    void move(int, int);

    //finds all fields where the figure from field i can move
    QVector<int> neighborFieldsToMove(int);
    //finds all fields that the figure must beat
    QVector<int> neighborFieldsToBeat(int);
    //sets correct neighbors to the all fields on the board
    void correctBoard();


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
    Color player; //what color of figures player plays

public slots:
    void isClicked(int i);
};

#endif // BOARD_H
