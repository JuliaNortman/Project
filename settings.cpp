#include "settings.h"
#include "ui_settings.h"

Settings::Settings(start* pStart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    startPage(pStart)
{
    ui->setupUi(this);
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
