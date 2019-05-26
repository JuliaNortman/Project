#pragma once

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVector>
#include "field.h"
#include "player.h"
#include "constants.h"


namespace Ui {
class Board;
}

class Player;

class Board : public QDialog
{
    Q_OBJECT

public:
    explicit Board(Player* player, QWidget *parent = nullptr);
    Board(const Board&);
    ~Board();
    void modelBoard(int);
    bool isBlackField(int);
    void markField(int);
    void deleteMark(int);
    void move(int from, int to);
    void undoMove(int from, int to, bool wasKing, bool king = false, bool hadBeat = false);
    //finds all fields where the figure from field i can move
    QVector<int> neighborFieldsToMove(int);
    //finds all fields that the figure must beat
    QVector<int> neighborFieldsToBeat(int);
    //sets correct neighbors to the all fields on the board
    void correctBoard();
    void setActivity(bool);
    void setCurrentPlayer(Player* pl){currentPlayer = pl;}/*sets current player who is active at the moment*/
    void gameEnd();/*returns true if the game is over*/
    int evaluateBoard(Color maximizer);/*evaluation of the current board state*/
    field getField(int i){return fields[i];}
    field* getBoardFields();
    void setBoardFields(field* f);

    QVector<int> getWhiteMove(){return whiteMove;}
    QVector<int> getBlackMove(){return blackMove;}
    QVector<int> getWhiteBeat(){return whiteBeats;}
    QVector<int> getBlackBeat(){return blackBeats;}
    QVector<int> getFieldBeats(int i){return fields[i].beats;}
    QVector<int> getFieldsMoves(int i){return fields[i].moves;}
    int getWhiteNumber(){return white;}
    int getBlackNumber(){return black;}
    /*sets from and to field after bot move*/
    void setActivePrevactive(int from, int to)
    {
        active = to;
        prevActive = from;
    }
    /*returns the field which figure will beat if it is a beat move
          while it moves 'from' 'to'*/
    int fieldToBeat(int from, int to);

protected:


    int white; //quantaty of white figures on the field
    int black; //quantaty of black figures on the field
    field *fields;
    int active = -1; //index of field that is clicked at the present moment
    int prevActive = -1; //index of the field that was clicked before the active
    bool whiteBeat; //true if white player needs to beat
    bool blackBeat; //true if black player needs to beat
    QVector<int> whiteMove; //indexes of the fields that white player can move from
    QVector<int> blackMove; //indexes of the fields that black player can move from
    QVector<int> whiteBeats; //indexes of the fields that white player can beat from
    QVector<int> blackBeats; //indexes of the fields that black player can beat from
    Color player; //what color is main player
    bool isActive = true; //true if board answer on the click

    Player* currentPlayer = nullptr;/*who is active at present moment*/




    public slots:
        void isClicked(int i);
    signals:
        void moved(Player*);/*emits when player has moved*/
        void end();

private:
    Ui::Board *ui;
};
