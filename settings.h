#pragma once

#include "start.h"
#include "player.h"
#include <QDialog>

namespace Ui {
class Settings;
}

class start;

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(start*, QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_okButton_clicked();

private:
    Ui::Settings *ui;
    start *startPage;
};

