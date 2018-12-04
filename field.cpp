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

field::field()
{
    king = false;
    empty = true;
    color = 0;
    coord = -1;
    needToBeat = false;
    checkerbutton = new ClickableLabel();
    beat = false;
}

field::~field()
{
}
