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
    void iniciarRonda();
    ~game();
public slots:
    void uiManager();
    void keyPressEvent(QKeyEvent *event);
private:
    player *jerry;
    arma *arma1;
    enemy *mantis;
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
    unsigned short mode;
    QGraphicsPixmapItem *healt[3];

    short ronda;

};

enum Mode{
    Pause, Play,
};

#endif // GAME_H
