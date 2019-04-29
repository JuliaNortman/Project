#pragma once
#include <QObject>
#include "constants.h"

class Figure : public QObject
{
    Q_OBJECT
public:
    explicit Figure(QObject *parent = nullptr);
    Figure(Color);
    void setKing(const bool& val){king = val;}
    void setColor(const Color& col){color = col;}
    bool isKing(){return king;}
    Color getColor(){return color;}
    void becomeKing() {king = true;}
    bool getBeat(){return hadBeat;}\
    void setBeat(bool beat){hadBeat = beat;}

private:
    bool king = false;
    Color color; //color of the figure
    bool hadBeat = false; /*whether the figure`s previos move was a beat move*/

signals:

public slots:
};
