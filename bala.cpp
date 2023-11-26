#include "bala.h"

bala::bala(float vy0_, float vx0_, int distancia, int tipo) : vy0(vy0_), vx0(vx0_), dis(distancia), tipo_(tipo)
{
    setPixmap(QPixmap(":/entidades/disparoLineal.png").scaledToHeight(5));
    cutSprites(":/entidades/explosion.png");

    time = new QTimer;
    animacion = new QTimer;

    animacion->setInterval(65);

    connect(time,SIGNAL(timeout()),this,SLOT(tiro()));
    connect(animacion, SIGNAL(timeout()), this, SLOT(switchAnimate()));

    index = 0;
    add = 1;
    used = false;

}

void bala::iniciar_tiro(int x0, int y0, QPoint dir)
{
    y = y0;
    x = x0;
    T = 0.01; //Periodo de muestreo en segundos
    n = 0;
    k = 5; //Factor de velocidad
    tempDir = dir;
    if(dir == Up) setRotation(0);
    if(dir == Down) setRotation(0);
    if(dir == Left) setRotation(180);
    if(dir == Right) setRotation(0);

    time->start(1000*T);
    setPos(x,y);
}

void bala::parar_tiro()
{
    if(!used)
    {
        if(tipo_ == 2)
        {
            used = true;
            animacion->start();
            time->stop();
        }

        else
        {
            used = true;
            time->stop();
            hide();
            delete this;
        }
    }
}

void bala::switchAnimate()
{

    setRotation(0);
    setPixmap(sprites[index].scaledToHeight(50));
    index += add;
    if (index >= 6 || index <= 0)
    {
        animacion->stop();
        hide();
        delete this;
    }

}

void bala::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    sprites.push_back(image.copy(0, 0, 77, 97));
    sprites.push_back(image.copy(78, 0, 86, 97));
    sprites.push_back(image.copy(162, 0, 86, 97));
    sprites.push_back(image.copy(248,0,85,97));
    sprites.push_back(image.copy(333,0,80,97));
    sprites.push_back(image.copy(413,0,80,97));
    sprites.push_back(image.copy(493,0,80,97));
}

bool bala::checkCollitions()
{
    bool colision = false;
    collitions = collidingItems();
    for(int i = 0; i < collitions.length(); i++)
    {
        if((typeid(*(collitions[i])) == typeid(QGraphicsRectItem)))
        {
            colision = true;
        }
    }
    return colision;
}

bala::~bala()
{
    delete time;
    delete animacion;
}

void bala::tiro()
{
    float posx, posy;

    if((tempDir == Left) || (tempDir == Right))
    {
        vy.setY(vy0 - ay*(k*n*T));
        vy.setX(0);
        vx.setY(0);
        vx.setX(vx0);

        posx = x+vx0*k*n*T*tempDir.x();
        posy = y-vy0*k*n*T+0.5*ay*(k*n*T*k*n*T); //ecuaciones de tiro parabolico

        setPos(posx,posy);

        if(posy > y || checkCollitions()) parar_tiro();
    }

    else if(tempDir == Down)
    {
        posx = x;
        if(tipo_ == 1) posy = y+35*(k*n*T*k*n*T);     // fisica de la bala de pistola
        else if(tipo_ == 2) posy = y-vy0*k*n*T+0.5*ay*(k*n*T*k*n*T); // fisica de la bala del lanzagranadas
        setRotation(90);
        setPos(posx,posy);
        if(posy > y + dis || checkCollitions()) parar_tiro();
    }
    else if(tempDir == Up)
    {
        posx = x;
        if(tipo_ == 1) posy = y-35*(k*n*T*k*n*T);
        else if(tipo_ == 2) posy = y-vy0*k*n*T-0.5*ay*(k*n*T*k*n*T);
        setRotation(270);
        setPos(posx,posy);
        if(posy < y - dis || checkCollitions()) parar_tiro();
    }
    n++;
}
