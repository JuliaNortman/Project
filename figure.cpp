#include "figure.h"

Figure::Figure(QObject *parent) : QObject(parent)
{
}

Figure::Figure(Color col)
    :color(col)
{
}
