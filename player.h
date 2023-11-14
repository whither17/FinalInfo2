#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "macros.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    player();
    void cutSprites(QString name);
    void cutSpritesDead(QString name);
    void setDirection(QPoint dir);
    void move();
    void usarArma();
    ~player();
    void setCanMove(bool newCanMove);

public slots:
    void switchAnimate();
    void animateDead();
    void isAnimate();
private:
    QTimer *jerryDead;
    std::vector<QPixmap> sprites;
    std::vector<QPixmap> spritesDead;
    short limit, index, cursor;

    QPoint tempDir, direccion;
    bool isAlive, canMove;

};

#endif // PLAYER_H
