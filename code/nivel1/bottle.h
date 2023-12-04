#ifndef BOTTLE_H
#define BOTTLE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <vector>
#include <string>
#include <QColor>

class bottle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
     bottle(int bottle_id,int x_pos,int y_pos);

    QPixmap getBorder_bottle() const;

public slots:

private:
    int bottle_id;
    int x_pos,y_pos;
    QPixmap border_bottle;

private slots:

};
#endif // BOTTLE_H
