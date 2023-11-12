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

class game : public QGraphicsView
{
    Q_OBJECT
public:
    game();
    void loadGame(QGraphicsView *n);
    void keyPressEvent(QKeyEvent *event);
    ~game();
private:
    player *jerry;
    QGraphicsRectItem *limites[5];
    QGraphicsScene *scene;
};

#endif // GAME_H
