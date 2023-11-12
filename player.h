#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include "macros.h"

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player();
    void cutSprites(QString name);
    ~player();
private:
    std::vector<QPixmap> sprites;

};

#endif // PLAYER_H
