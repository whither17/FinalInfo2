#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <vector>
#include <QTimer>
#include <QElapsedTimer>
#include "../macros.h"
#include "bala.h"
#include "player.h"

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy();
    void cutSprites(QString name);
    void setDirection(QPoint dir);
    void setJerry(player *newJerry);  
    void wait(qreal msec);  
    //~enemy();

    void setIsAlive(bool newIsAlive);

public slots:
    void distEnemy(int x_, int y_);
    void checkCollitions();
    void switchAnimate();
    void eliminar();
    void move();
    void die();
    void resume();
    void pause();

signals:
    void muerto();
    void atac();
    void Drop(int x, int y);
private:
    std::vector<QPixmap> spritesRight;
    std::vector<QPixmap> spritesLeft;
    QPoint tempDir, direccion;
    QMediaPlayer *soundDead, *soundDamage;
    QAudioOutput *audioOutput1, *audioOutput2;
    QList<QGraphicsItem*> collitions;
    short index, limit, healt;
    int speed;
    player *jerry;
    bala *b1;
    bool isAlive;
    bool isDrop;
    QTimer *animateTimer;
    QElapsedTimer timer;

};

#endif // ENEMY_H
