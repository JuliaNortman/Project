#include "settings.h"
#include "ui_settings.h"

Settings::Settings(start* pStart,Color color, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    startPage(pStart)
{
    ui->setupUi(this);
    if(color == Color::WHITE)
    {
        ui->whiteRadioButton->setChecked(true);
    }
    else ui->blackRadioButton->setChecked(true);
}


Settings::~Settings()
{
    delete ui;
}

void Settings::on_okButton_clicked()
{
    Player* p1 = nullptr;
    Player* p2 = nullptr;
    if(ui->whiteRadioButton->isChecked())
    {
        p1 = new Person(Color::WHITE);
    }
    else if(ui->blackRadioButton->isChecked())
    {
        p1 = new Person(Color::BLACK);
    }
    if(ui->botRadioButton->isChecked())
    {
        if(!ui->whiteRadioButton->isChecked())
        {
            p2 = new Bot(Color::WHITE);
        }
        else if(!ui->blackRadioButton->isChecked())
        {
            p2 = new Bot(Color::BLACK);
        }
    }
    startPage->setPlayers(p1, p2);
    this->close();
}
