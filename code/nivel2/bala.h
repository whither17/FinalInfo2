#ifndef BALA_H
#define BALA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <vector>
#include <QTimer>
#include "../macros.h"
#include <math.h>

class bala : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bala(float vy0_, float vx0_, int distancia, int tipo);

    void iniciar_tiro(int x0, int y0, QPoint dir);
    bool checkCollitions();
    ~bala();
    
public slots:
    void tiro();
    void parar_tiro();
    void switchAnimate();

private:
    void cutSprites(QString name);
    std::vector<QPixmap> sprites;
    QList<QGraphicsItem*> collitions;
    QPoint vy, vx, tempDir;

    float x,y,T,k, vy0, vx0;
    unsigned int n;
    int dis, tipo_;
    short index, add;
    QTimer *animacion, *time;
    bool used;

};

#endif // BALA_H
