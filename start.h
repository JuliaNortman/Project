#ifndef START_H
#define START_H

#include <QDialog>
#include "field.h"

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

#endif // START_H
