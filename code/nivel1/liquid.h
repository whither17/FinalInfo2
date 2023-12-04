#ifndef LIQUID_H
#define LIQUID_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <iostream>

class Liquid: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Liquid(const QColor &target_color, const QColor &replacement_color, int position_id);

    QColor none=QColor(0,0,0);

    QPixmap getLiquidbase() const;
    bool isitvoid();


    QColor getReplacement_color() const;

    int getPosition_id() const;

public slots:

private:
    void change_pixmap_color(QPixmap &pixmap);
    int position_id;
    int x_pos,y_pos;
    QColor target_color;
    QColor replacement_color;
    QPixmap Liquidbase;
    QPixmap selectpicture(int id);

private slots:

};

#endif // LIQUID_H
