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
    checkerbutton = obj.checkerbutton;
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
