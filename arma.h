#ifndef ARMA_H
#define ARMA_H

#include <QObject>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "bala.h"
#include "macros.h"


class arma : public QObject, public QGraphicsPixmapItem
{
public:
    arma(int tipo_, QGraphicsScene *scene);
    void cutSprites(QString name);
    void setDirection(QPoint dir_);
    int getMunicion() const;
    bala *getBala();
    void setMunicion(int newMunicion);

public slots:
    void mover(int x, int y);
    void disparar();

private:
    std::vector<QPixmap> sprites;
    int municion;
    short tipo;
    QGraphicsScene *scena;
    float vx0;
    float vy0;
    int distanciaTiro1;
    bala *b1;
    QPoint dir;
};

#endif // ARMA_H
