#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "macros.h"
#include "bala.h"
#include "player.h"

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QTimer *animateTimer;
    enemy();
    void cutSprites(QString name);
    void setDirection(QPoint dir);
    void attack();
    void setJerry(player *newJerry);
    void resume();
    void pause();

public slots:
    void distEnemy(int x_, int y_);
    void checkCollitions();
    void switchAnimate();
    void move();
    void die();
signals:
    void muerto();
    void atac();
private:
    std::vector<QPixmap> spritesRight;
    std::vector<QPixmap> spritesLeft;
    QPoint tempDir, direccion;
    QList<QGraphicsItem*> collitions;
    short index, limit, healt;
    int speed;
    player *jerry;
    bala *b1;
    bool isAlive;

};

#endif // ENEMY_H
