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
#include "macros.h"
#include "bala.h"

class game : public QGraphicsView
{
    Q_OBJECT
public:
    player *jerry;
    game();
    void loadGame();
    void colliderLimits(player *pl);
    ~game();
public slots:
    void keyPressEvent(QKeyEvent *event);
private:
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
    unsigned short mode;
};

enum Mode{
    Pause, Play,
};

#endif // GAME_H
