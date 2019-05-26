#include "start.h"
#include "ui_start.h"
#include "field.h"
#include "board.h"
#include "player.h"
#include "game.h"
#include "settings.h"

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    int k = 0;
    k = 9;
    ClickableLabel *lbl = new ClickableLabel;
    ui->startLable->addWidget(lbl);
    QPixmap checkerbuttonPix(":/img/Images/start.png");
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
    k = 9;
    if(!player1)
    {
        player1 = new Person(Color::WHITE);
    }
    if(!player2)
    {
        player2 = new Bot(Color::BLACK);
    }
    if(player1->getColor() == Color::WHITE) game = new Game(player1, player2);
    else game = new Game(player2, player1);
    this->close();
}

void start::setPlayers(Player *pl1, Player *pl2)
{
    if(player1) delete player1;
    if(player2) delete player2;
    player1 = pl1;
    player2 = pl2;
}

void start::on_toolButton_clicked()
{
    if(player1 && player1->getColor() == Color::BLACK)
    {
        s = new Settings(this, Color::BLACK);
    }
    else
    {
        s = new Settings(this, Color::WHITE);
    }
    s->exec();
}
