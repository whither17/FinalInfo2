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
    void setDirection(QPoint dir);
    void move();
    ~player();
public slots:
    void switchAnimate();
private:
    std::vector<QPixmap> sprites;
    unsigned short limit, index, vista;
    QTimer *jerryMove;
    QPoint tempDir, direccion;
    bool isAlive;

};

#endif // PLAYER_H
