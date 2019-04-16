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
    emit clicked(index);
}

void ClickableLabel::indexChange(int i)
{
    index = i;
}

field::field(Color fColor, int coord)
    :fieldColor(fColor), coordinate(coord), beat(false)
{
    //king = false;
    //empty = true;
    //coord = -1;
    //needToBeat = false;
    //checkerbutton = new ClickableLabel();
}

field::field(const field& obj)
    :fieldColor(obj.fieldColor), coordinate(obj.coordinate)
{
    beat = obj.beat;
    moves = obj.moves;
    beats = obj.beats;
    figure = new Figure;
    figure->setKing(obj.figure->isKing());
    figure->setColor(obj.figure->getColor());
    checkerbutton = new ClickableLabel;
    checkerbutton->index = obj.checkerbutton->index;
}

field::~field()
{
    delete figure;
    delete checkerbutton;
}

void field::setFigure(Figure *fig)
{
    figure = fig;
}
Figure* field::removeFigure()
{
    Figure* f = figure;
    figure = nullptr;
    return f;
}

 Figure* field::getFigure()
 {
     return figure;
 }

 void field::setPicture(const QString& path)
 {
     QPixmap checkerbuttonPix(path);
     checkerbutton->setPixmap(checkerbuttonPix);
     checkerbutton->setScaledContents(true);
 }

 void field::setPicture()
 {
     if(fieldColor == Color::WHITE) setPicture(whiteField);
     else
     {
         if(!figure) setPicture(blackField);
         else if(figure->getColor() == Color::WHITE)
         {
             if(figure->isKing()) setPicture(whiteKing);
             else setPicture(whiteSimpleFigure);
         }
         else  if(figure->getColor() == Color::BLACK)
         {
             if(figure->isKing()) setPicture(blackKing);
             else setPicture(blackSimpleFigure);
         }
      }
 }

 void field::markField()
 {
     if(!figure && fieldColor == Color::BLACK) setPicture(blackChosenField);
     else if(figure->getColor() == Color::WHITE)
     {
         if(figure->isKing()) setPicture(whiteChosenKing);
         else setPicture(whiteChosenFigure);
     }
     else  if(figure->getColor() == Color::BLACK)
     {
         if(figure->isKing()) setPicture(blackChosenKing);
         else setPicture(blackChosenFigure);
     }
 }

 void field::unmarkField()
 {
     setPicture();
 }

 void field::addMove(int i)
 {
     moves.push_back(i);
 }

 bool field::canMoveTo(int to)
 {
     for(int i = 0; i < beats.size(); ++i)
     {
         if(beats[i] == to) return true;
     }
     for(int i = 0; i < moves.size(); ++i)
     {
         if(moves[i] == to) return true;
     }
     return false;
 }
