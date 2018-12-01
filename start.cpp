#include "start.h"
#include "ui_start.h"
#include "field.h"
#include "board.h"

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    int k = 0;
    ClickableLabel *lbl = new ClickableLabel;
    ui->startLable->addWidget(lbl);
    QPixmap checkerbuttonPix("Images/start.png");
    lbl->setPixmap(checkerbuttonPix);
    lbl->setScaledContents(true);
    connect(lbl, SIGNAL(clicked(int)), this, SLOT(startGame(int)));
}

start::~start()
{
    delete ui;
}

void start::startGame(int k)
{
    Board *b = new Board;
    b->show();
    this->close();
}
