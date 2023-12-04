#ifndef PLAYER_H
#define PLAYER_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QObject>
#include <QTimer>
#include <vector>
#include "../macros.h"
#include "arma.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    player(QGraphicsScene *scene, QString sprite, short borde, short d_anch, short d_alt, short scala);
    void setTipo_arma(int newTipo_arma);
    void cutSpritesDead(QString name);
    void setCanMove(bool newCanMove);
    void setIsAlive(bool newIsAlive);
    void cutSprites(QString name, short borde, short ancho_transparente, short alto_transparente);
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

    void setScale(short newScale);

    void setTieneArma(bool newTieneArma);

    bool getIsAlive() const;

public slots:
    void switchAnimate();
    void animateDead();
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
    short limit, index, cursor, lives, scale;
    int municion1, municion2, tipo_arma, score;
    bool isAlive, canMove, tieneArma;

};

#endif // PLAYER_H
