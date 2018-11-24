#ifndef BOARD_H
#define BOARD_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVector>
#include "field.h"

class Board :public field
{
    Q_OBJECT
public:
    Board();
    ~Board();
    void modelBoard(int);
    void setPicture(int, QString);
    bool isBlackField(int);
    bool isNeighbor(int, int);
    void markField(int); //выделить белую фигуру и её соседей
    void deleteMark(int); //убрать выделение с белой фигуры и её соседей
    void analyseField();
    bool needToBeatThisField(int, int);
    bool canMove(int, int);
    void analyseKingField(bool&, int, QVector<int>&); //function that is used in ana;yseField for kings
    void analyseSimpleField(bool&, int, int, QVector<int>&);
    void move(int, int);


protected:
    int white; //quantaty of available white figures on the field
    int black; //quantaty of available black figures on the field
    field *fields;
    int active; //index of field that is active at the present moment
    int prevActive;
    bool whiteBeat; //checks whether is needed to beat white figure
    bool blackBeat; //checks whether is needed to beat black figure
    QVector<int> whiteMove; //all white possible moves
    QVector<int> blackMove;
    /*int *mustBeatWhite;
    int *mustBeatBlack;*/
public slots:
    void isClicked(int i);
};

#endif // BOARD_H
