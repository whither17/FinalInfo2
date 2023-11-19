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
    QTimer *animateTimer;
    enemy();
    void cutSprites(QString name);
    void setDirection(QPoint dir);
    void attack();
public slots:
    void distEnemy(int x_, int y_);
    void switchAnimate();
    void move();

signals:

    void atac();
private:
    std::vector<QPixmap> spritesRight;
    std::vector<QPixmap> spritesLeft;

    QPoint tempDir, direccion;
    short index, limit;

};

#endif // ENEMY_H
