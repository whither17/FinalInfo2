#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <vector>
#include <QTimer>
#include "macros.h"
#include "arma.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    player(QGraphicsScene *scene);
    void cutSprites(QString name);
    void cutSpritesDead(QString name);
    void setDirection(QPoint dir);
    void move(bool mover);
    void cambiarArma(int tipo);
    void usarArma();
    ~player();
    void setCanMove(bool newCanMove);

    short getLives() const;

    QPoint getTempDir() const;

public slots:
    void switchAnimate();
    void animateDead();
    void isAnimate();
    void posicionActual();
    void damage();
signals:
    void movement(int x, int y);
    void fail();
private:
    QGraphicsScene *scena;
    QTimer *jerryDead, *JerryMove;
    std::vector<QPixmap> sprites;
    std::vector<QPixmap> spritesDead;
    short limit, index, cursor, lives, salud;
    arma *arma1;
    QPoint tempDir, direccion;
    bool isAlive, canMove;

};

#endif // PLAYER_H
