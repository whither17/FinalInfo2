#ifndef PP_H
#define PP_H
#include "bottle.h"
#include "liquid.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <vector>
#include <string>
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QTransform>

class pp:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    pp(int id,int x, int y);
    QPixmap getPicturefinal() const;
    int objective=-1;
    int getX();
    void onclik1();
    void onclik2();
    void bottledance1();
    void bottledance2();
    int getY();
    bool searchvoids();
    int getId() const;
    void fillspace(Liquid* newL);
    Liquid* emptyspace();
    void setObjective(int newObjective);
    void updatepixmap();
    void returnToposition();

private:
    void rotatePixmap(int control);
    QPixmap combinePixmaps(const QPixmap &pixmap1, const QPixmap &pixmap2,int idi);
    const QColor green=QColor(0,200,0);
    const QColor target_color = QColor(255, 255, 255);
    const QColor pink=QColor(255,192,203);
    const QColor yellow=QColor(238,210,2);
    const QColor none=QColor(0,0,0);
    bool movement;
    bottle *cuerpo;
    Liquid *l1,*l2,*l3;
    int id,x,y,angle=0,originalX,originalY;
    short danceid=0;
    QPixmap picturefinal;
    QTimer *crono,*crono2,*cr3,*cr4;
    std::vector<Liquid*> posiciones;
private slots:
    void firstStateofmovement();
    void secondStateofmovement();
    void rotation();
    void rotation2();
    void acelerationmovement();
    void acelerationmovement2();
    void backtoposition();
signals:
    void finrotacion();
};

#endif // PP_H
