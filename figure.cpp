#include "figure.h"

Figure::Figure(QObject *parent) : QObject(parent)
{
}

/**
 * @brief Constructor
 */
Figure::Figure(Color col)
    :color(col)
{
}
