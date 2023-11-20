#include "arma.h"

arma::arma(int tipo_, QGraphicsScene *scene)
{
    tipo = tipo_;
    if(tipo_ == 1)
    {
        cutSprites(":/entidades/gun.png");
        municion = 30;
        vx0 = 160;
        vy0 = 8;
        distanciaTiro1 = 10000;

    }

    else if(tipo_ == 2)
    {
        cutSprites(":/entidades/lanzagranadas.png");
        setPixmap(sprites[0].scaledToHeight(15));
        municion = 10;
        vx0 = 70;
        vy0 = 15;
        distanciaTiro1 = 100;
    }
    scena = scene;
}

void arma::cutSprites(QString name)
{
    if(tipo == 1)
    {
        QPixmap image;
        image.load(name);

        sprites.push_back(image.copy(0, 0, gun_largo, gun_alto));
        sprites.push_back(image.copy(gun_largo, 0, 2*gun_largo, gun_alto));
    }
    else if(tipo == 2)
    {
        QPixmap image;
        image.load(name);

        sprites.push_back(image.copy(0, 0, 763, 236));
        sprites.push_back(image.copy(763, 0, 2*763, 236));
    }

}

void arma::setDirection(QPoint dir_)
{
    dir = dir_;
    if(dir == Left) setPixmap(sprites[0].scaledToHeight(15));
    else if(dir == Right) setPixmap(sprites[1].scaledToHeight(15));
    else setPixmap(sprites[0].scaledToHeight(1));
}

void arma::mover(int x, int y)
{
    if(tipo == 1)
    {
        if(dir == Left)
        {
            setPos(x-6, y+alto_Jerry/3);
        }
        else if(dir == Right)
        {
            setPos(x+28, y+alto_Jerry/3);
        }
        else setPos(x, y+alto_Jerry/3);
    }
    if(tipo == 2)
    {
        if(dir == Left)
        {
            setPos(x-6, y+alto_Jerry/3);
        }
        else if(dir == Right)
        {
            setPos(x+2, y+alto_Jerry/3);
        }
        else setPos(x, y+alto_Jerry/3);
    }
}

void arma::disparar()
{
    municion--;
    if(municion > 0)
    {
        b1 = new bala(vy0, vx0, distanciaTiro1, tipo);
        b1->setPos(x(), y());
        scena->addItem(b1);
        b1->iniciar_tiro(x(), y(), dir);
    }
    else municion = 0;
}

int arma::getMunicion() const
{
    return municion;
}

bala *arma::getBala()
{
    return b1;
}

void arma::setMunicion(int newMunicion)
{
    municion = newMunicion;
}

