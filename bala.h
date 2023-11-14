#ifndef BALA_H
#define BALA_H
#include <QObject>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include "macros.h"
#include <math.h>

class bala : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bala();
    QTimer *time;
    void iniciar_tiro(int x0, int y0, QPoint dir);
private slots:
    void tiro();
    void parar_tiro();
    void switchAnimate();

private:
    void cutSprites(QString name);
    std::vector<QPixmap> sprites;
    QPoint vy, vx, vect_dr, tempDir;
    float x,y,T,k;
    unsigned int n;
    double angle, tang_angle;
    short index, add;
    QTimer *animacion;

};

#endif // BALA_H
