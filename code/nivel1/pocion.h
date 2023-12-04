#ifndef POCION_H
#define POCION_H
#include "bottle.h"
#include "liquid.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <vector>
#include <string>
#include <QColor>
#include <QLabel>
class Pocion: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pocion(const QColor &target_color, const QColor &replacement_color, int id,int x, int y);
    void printall();
    QPixmap combinePixmaps(const QPixmap &pixmap1, const QPixmap &pixmap2);
private:
    QColor target_color;
    QColor replacement_color;
    bottle *cuerpo;
    Liquid *l1,*l2,*l3;
    int id,x,y;
    QPixmap picturefinal;
    QLabel label;
};

#endif // POCION_H
