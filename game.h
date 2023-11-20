#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QDialog>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QEventLoop>
#include <QWidget>
#include "player.h"
#include "enemy.h"
#include "arma.h"
#include "macros.h"

class game : public QGraphicsView
{
    Q_OBJECT
public:
    game();
    void loadGame();
    bool colliderLimits(player *pl);
    void loadDock();
    void win();
    void wait(qreal msec);
    void resume();
    void pause();
    ~game();
public slots:
    void uiManager();
    void roundManager();
    void cargarEnemigos();
    void remainingEnemies();
     void countDown();
    void keyPressEvent(QKeyEvent *event);
signals:
    void fail();
private:
    player *jerry;
    arma *arma1;
    enemy *newMantis;
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
    unsigned short mode;
    QGraphicsPixmapItem *healt[3];
    QGraphicsTextItem *t_puntos, *n_puntos, *n_municion , *t_arma, *t_ronda, *n_ronda;
    short round,amountOfEnemies, killEnemies, round_n;
    QTimer *rondaTimer, *lag;
};

enum Mode{
    Pause, Play,
};

#endif // GAME_H
