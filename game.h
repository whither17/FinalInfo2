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
#include "macros.h"
#include "bala.h"

class game : public QGraphicsView
{
    Q_OBJECT
public:

    game();
    void loadGame();
    bool colliderLimits(player *pl);
    ~game();
public slots:
    void keyPressEvent(QKeyEvent *event);
private:
    player *jerry;
    enemy *mantis;
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
    unsigned short mode;
};

enum Mode{
    Pause, Play,
};

#endif // GAME_H
