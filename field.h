#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "constants.h"
#include "figure.h"



class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=nullptr );
    ~ClickableLabel();
    int index;//index of the field[0..SIZE]
    bool active = true;//true if the field will answer on the click
    void indexChange(int);

signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class field : public QMainWindow
{
    Q_OBJECT
public:
    field() = default;
    field(Color fColor, int coord); //constructor
    field(const field&); //copy constructor
    field& operator= (const field&);
    ~field();

    void setFigure(Figure*);
    Figure* removeFigure(); //remove figure from the field
    Figure* getFigure();
    void setColor(Color c){fieldColor = c;}
    Color getColor(){return fieldColor;}
    void setCoordinate(int coord){coordinate = coord;}
    int getCoordinate(){return coordinate;}
    void setBeat(bool beat){this->beat = beat;}
    bool getBeat(){return beat;}
    void setActive(bool active);
    ClickableLabel* getCheckerbutton(){return checkerbutton;}

    //sets correct picture according to the field color and figure
    void setPicture();
    //marks field as chosen
    void markField();
    void unmarkField(); //make the field as unchosen
    void addMove(int);
    bool canMoveTo(int);

    QVector<int> moves; //all possible moves from this field
    QVector<int> beats; //all possible beat moves from the field

private:
    Color fieldColor = Color::WHITE; //field`s color
    int coordinate = -1; //field index on the board
    Figure* figure = nullptr; //figure on the field
    bool beat; // whether the figure on this field needs to beat
    ClickableLabel *checkerbutton = new ClickableLabel;

    // sets picture of the field
    // QString path - path of the picture
    void setPicture(const QString& path);
};


