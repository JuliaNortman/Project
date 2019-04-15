#ifndef FIELD_H
#define FIELD_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "mainwindow.h"
#include "constants.h"
#include "figure.h"



class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=nullptr );
    ~ClickableLabel();
    int index;
    void indexChange(int);

signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class field : public MainWindow
{
    Q_OBJECT
public:
    field() = default;
    field(Color fColor, int coord); //constructor
    field(const field&); //copy constructor
    ~field();

    void setFigure(Figure*);
    Figure* removeFigure(); //remove figure from the field
    Figure* getFigure();
    void setColor(Color c){fieldColor = c;}
    void setCoordinate(int coord){coordinate = coord;}
    ClickableLabel* getCheckerbuttton

private:
    QVector<int> moves; //all possible moves from this field
    QVector<int> beats; //all fields that the figure on this field needs to beat
    Color fieldColor = Color::WHITE;
    int coordinate = -1; //field coordinate on the board
    Figure* figure = nullptr;
    bool beat; // whether it is needed to beat this field or not
    ClickableLabel *checkerbutton = new ClickableLabel;





    //bool king;
    //bool empty;
    //bool needToBeat;

    //Color color;
    //int coord;
    //ClickableLabel *checkerbutton;
};




#endif // FIELD_H
