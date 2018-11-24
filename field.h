#ifndef FIELD_H
#define FIELD_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "mainwindow.h"



class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=nullptr );
    ~ClickableLabel();
    int index;
    void indexChange(int);


    //friend void isClicked(int);
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class field : public MainWindow
{
    Q_OBJECT
public:
    field();
    ~field();
    bool king;
    bool empty;
    bool needToBeat;
    QVector<int> neighbors;
    int color;
    int coord;
    ClickableLabel *checkerbutton;
    //friend class MainWindow;
    //void mousePressEvent(QMouseEvent* event);


    //friend void isClicked(int);

/*signals:
    void clicked(int);*/
};




#endif // FIELD_H
