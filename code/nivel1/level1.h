#ifndef LEVEL1_H
#define LEVEL1_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRectF>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <qlabel.h>
#include "bottle.h"
#include "liquid.h"
#include "pocion.h"
#include "pp.h"


class level1 : public QGraphicsView
{
    Q_OBJECT

public:
    level1();
    ~level1();
    pp* searchpp(int id);

public slots:
    void channgeLiquid();

private:
    pp *emisore;
    void secondanimation(int emisor,pp *receptor);
    QGraphicsScene *scene;
    void mousePressEvent(QMouseEvent *event);
    QRectF colisiorect(pp* base);
    std::vector<pp*> pocimas;
    pp *pp2,*pp1,*pp3,*pp4;
    int movement_status=0,pocionarriba=-1,pocionreceptor=-1;
    QGraphicsRectItem *tt;

};
#endif // LEVEL1_H
