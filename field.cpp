#include <QPushButton>
#include <QStyle>
#include <QLabel>
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
    neighbors = new int [4];
    beat = new int [4];
    for(int i = 0; i < 4; ++i)
    {
        neighbors[i] = beat[i] = -1;
    }
    color = 0;
    coord = -1;
    needToBeat = false;
    checkerbutton = new ClickableLabel();

}


field::~field()
{
   // delete [] neighbors;
   // delete [] beat;
}
