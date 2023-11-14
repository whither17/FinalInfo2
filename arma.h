#ifndef ARMA_H
#define ARMA_H

#include <QObject>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "macros.h"
#include <math.h>

class arma : public QObject, public QGraphicsPixmapItem
{
public:
    arma();
};

#endif // ARMA_H
