#ifndef FIELD_H
#define FIELD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "mainwindow.h"


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
    field();
    ~field();
    bool king;
    bool empty;
    bool needToBeat;
    int *neighbors;
    int *beat;
    int color;
    int coord;
    ClickableLabel *checkerbutton;
};




#endif // FIELD_H
