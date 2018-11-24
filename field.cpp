#include <QPushButton>
#include <QStyle>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "field.h"


ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    qDebug() << QString::number(index) + ": MouseClicked ";
    emit clicked(index);

    //isClicked(index);
    //event->x();
    qDebug() << "after";
}

void ClickableLabel::indexChange(int i)
{
    qDebug() << "i: "+QString::number(i);
    index = i;
    qDebug() << "index: "+QString::number(index);
}

field::field()
{
    king = false;
    empty = true;
    /*neighbors = new int [4];
    beat = new int [4];*/
    /*for(int i = 0; i < 4; ++i)
    {
        neighbors[i] = beat[i] = -1;
    }*/
    color = 0;
    coord = -1;
    needToBeat = false;
    checkerbutton = new ClickableLabel();

}

/*void field::mousePressEvent(QMouseEvent* event)
{
    emit clicked(coord);
}*/

field::~field()
{
   // delete [] neighbors;
   // delete [] beat;
}
