#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
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
protected:
    int white;
    int black;
    field *fields;
    int active;
    int prevActive;
    int *mustBeatWhite;
    int *mustBeatBlack;
public slots:
    void isClicked(int i);
};

#endif // BOARD_H
