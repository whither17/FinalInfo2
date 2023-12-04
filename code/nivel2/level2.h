#ifndef level2_H
#define level2_H

#include <QObject>
#include <QGraphicsView>
#include <QDialog>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QWidget>
#include <random>
#include "player.h"
#include "enemy.h"
#include "arma.h"
#include "../macros.h"
#include "item.h"

class level2 : public QGraphicsView
{
    Q_OBJECT
public:
    level2();
    void loadlevel2();
    bool colliderLimits(player *pl);
    void loadDock();
    void win();
    void waitDead(qreal msec);
    void wait(qreal msec);
    void resume();
    void pause();
    ~level2();
public slots:
    void uiManager();
    void roundManager();
    void cargarEnemigos();
    void remainingEnemies();
    void generateDrop(int x, int y);
    void gameFail();
    void keyPressEvent(QKeyEvent *event);

signals:
    void winer();

private:
    item *it;
    player *jerry;
    enemy *newMantis;
    std::vector<enemy*> enemies;
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
    unsigned short mode;
    QGraphicsPixmapItem *healt[3];
    QGraphicsTextItem *t_puntos, *n_puntos, *n_municion , *t_arma, *t_ronda, *n_ronda;
    short round, killEnemies, round_n;
    QTimer *rondaTimer;
    QElapsedTimer *timer;
    QMediaPlayer *sound;
    QAudioOutput *audioOutput;
};

enum Mode{
    Pause, Play,
};

#endif // level2_H
