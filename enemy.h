#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "macros.h"

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy();
    void cutSprites(QString name);
    void setDirection(QPoint dir);
public slots:
    void switchAnimate();
private:
    std::vector<QPixmap> sprites;
    QPoint tempDir, direccion;
    short cursor, index, limit;
    QTimer *animateTimer;
};

#endif // ENEMY_H
