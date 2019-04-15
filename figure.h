#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include "constants.h"

class Figure : public QObject
{
    Q_OBJECT
public:
    explicit Figure(QObject *parent = nullptr);
    void setKing(const bool& val){king = val;}
    void setColor(const Color& col){color = col;}
    bool isKing(){return king;}
    Color getColor(){return color;}
    void becomeKing() {king = true;};

private:
    bool king;
    Color color; //color of the figure

signals:

public slots:
};

#endif // FIGURE_H
