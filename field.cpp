#include <QPushButton>
#include <QStyle>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include "field.h"


ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel()
{
}

/**
 * @brief react on the left mouse click
 */
void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton && active)
    {
        emit clicked(index);
    }
}

/**
 * @brief sets correct index
 * @param i Index that should be set
 */
void ClickableLabel::indexChange(int i)
{
    index = i;
}

/**
 * @brief Constructor
 */
field::field(Color fColor, int coord)
    :fieldColor(fColor), coordinate(coord), beat(false)
{
}

/**
 * @brief Copy constructor
 */
field::field(const field& obj)
{
    fieldColor = obj.fieldColor;
    coordinate = obj.coordinate;
    beat = obj.beat;
    moves = obj.moves;
    beats = obj.beats;
    figure = new Figure;
    if(obj.figure)
    {
        figure->setKing(obj.figure->isKing());
        figure->setColor(obj.figure->getColor());
        figure->setBeat(obj.figure->getBeat());
    }
    else figure = nullptr;
    checkerbutton = new ClickableLabel;
    checkerbutton->index = obj.checkerbutton->index;
    checkerbutton->active = obj.checkerbutton->active;
}

field& field::operator=(const field &obj)
{
    if(this != &obj)
    {
        this->~field();
        fieldColor = obj.fieldColor;
        coordinate = obj.coordinate;
        beat = obj.beat;
        moves = obj.moves;
        beats = obj.beats;
        figure = new Figure;
        if(obj.figure)
        {
            figure->setKing(obj.figure->isKing());
            figure->setColor(obj.figure->getColor());
            figure->setBeat(obj.figure->getBeat());
        }
        else figure = nullptr;
        checkerbutton = new ClickableLabel;
        checkerbutton->index = obj.checkerbutton->index;
        checkerbutton->active = obj.checkerbutton->active;
    }
    return *this;
}

/**
 * @brief Destructor
 */
field::~field()
{
    if(figure)
    {
        delete figure;
        figure = nullptr;
    }
    delete checkerbutton;
}

/**
 * @brief set figure on the field
 * @param fig Figure that should be set
 */
void field::setFigure(Figure *fig)
{
    figure = fig;
}

/**
 * @brief remove figure from the field
 * @return removed figure
 */
Figure* field::removeFigure()
{
    Figure* f = figure;
    figure = nullptr;
    return f;
}

/**
  * @brief get figure
  * @return figure that is on the field or nullptr if there is no figure
  */
 Figure* field::getFigure()
 {
     return figure;
 }

 /**
  * @brief sets picture on the field
  * @param path Path of the picture
  */
 void field::setPicture(const QString& path)
 {
     QPixmap checkerbuttonPix(path);
     checkerbutton->setPixmap(checkerbuttonPix);
     checkerbutton->setScaledContents(true);
 }


 /**
  * @brief choose what picture should be set according to the parametres of the field
  * and set the picture
  */
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

 /**
  * @brief set whether the field should react on mouse click
  * @param active - thrue if the field should react on click
  * false otherwise
  */
 void field::setActive(bool active)
 {
     checkerbutton->active = active;
 }

 /**
  * @brief choose what picture should be set onthe field when it is clicked
  */
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

 /**
  * @brief set correct picture on the field
  */
 void field::unmarkField()
 {
     setPicture();
 }

 /**
  * @brief add possible move to the vector of moves
  * @param i Index of the field for possible moves
  */
 void field::addMove(int i)
 {
     moves.push_back(i);
 }

 /**
  * @brief checks whether the figure on the field can move to the field with index to
  * @param to Field where figure need to move
  * @return true if the move is allowed
  * false otherwise
  */
 bool field::canMoveTo(int to)
 {
     //checks if figure need to beat on the field with index to
     for(int i = 0; i < beats.size(); ++i)
     {
         if(beats[i] == to)
             return true;
     }
     //checks if figure need to move on the field with index to
     for(int i = 0; i < moves.size(); ++i)
     {
         if(moves[i] == to) return true;
     }
     return false;
 }
