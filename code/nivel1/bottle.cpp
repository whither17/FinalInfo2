#include "bottle.h"
#include <QGraphicsPixmapItem>

bottle::bottle(int bottle_id,int x_pos,int y_pos)
{
    QPixmap cc(":/level1/textures/level1/botella.png");
    this->bottle_id = bottle_id;
    this->border_bottle=cc.copy();
}

QPixmap bottle::getBorder_bottle() const
{
    return border_bottle;
}
