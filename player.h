#ifndef PLAYER_H
#define PLAYER_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QObject>
#include <QTimer>
#include <vector>
#include "macros.h"
#include "arma.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    player(QGraphicsScene *scene);
    void setTipo_arma(int newTipo_arma);
    void cutSpritesDead(QString name);
    void setCanMove(bool newCanMove);
    void setIsAlive(bool newIsAlive);
    void cutSprites(QString name);
    void setDirection(QPoint dir);
    void cambiarArma(int tipo);
    void move(bool mover);
    void usarArma();
    void pause();
    void dead();
    void play();
    short getLives() const;
    QPoint getTempDir() const;
    int getMunicion() const;
    bala *getBala();
    int getTipo_arma() const;
    int getScore() const;
    void setScore(int newScore);
    void setLives(short newLives);
    void restartArma();
    ~player();

public slots:
    void switchAnimate();
    void animateDead();
    void isAnimate();
    void posicionActual();
    void addScore();
    void damage();
    void powerUp(int a);

signals:
    void movement(int x, int y);
    void fail();

private:
    QGraphicsScene *scena;
    QTimer *jerryDead, *JerryMove;
    QPoint tempDir, direccion;
    QMediaPlayer *sound;
    QAudioOutput *audioOutput;
    std::vector<QPixmap> sprites;
    std::vector<QPixmap> spritesDead;
    arma *arma1, *arma2;
    short limit, index, cursor, lives;
    int municion1, municion2, tipo_arma, score;
    bool isAlive, canMove;

};

#endif // PLAYER_H
