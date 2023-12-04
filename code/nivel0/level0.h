#ifndef LEVEL0_H
#define LEVEL0_H

#include <QObject>
#include <QGraphicsView>
#include <QDialog>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QEventLoop>
#include <QWidget>
#include <random>
#include "../nivel2/player.h"
#include "../nivel2/enemy.h"
#include "../nivel2/arma.h"
#include "../macros.h"
#include "../nivel2/item.h"

class level0 : public QGraphicsView
{
    Q_OBJECT
public:
    level0(short level_);
    void loadLevel1();
    void loadLevel2();
    void keyPressEvent(QKeyEvent *event);
signals:
    void irNivel(int n);

private:
    void irAnivel1();
    void irAnivel2();
    void transformacion();
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
    player *morty;
    QGraphicsPixmapItem *entidad;
    short level;
};

#endif // LEVEL0_H
