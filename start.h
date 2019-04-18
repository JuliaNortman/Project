#pragma once

#include <QDialog>
#include "field.h"
#include "mainwindow.h"

namespace Ui {
class start;
}

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();
public slots:
    void startGame(int);
private:
    Ui::start *ui;
};

