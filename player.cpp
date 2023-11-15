#include "player.h"

player::player()
{
    cutSprites(":/entidades/Jerry.png");
    cutSpritesDead(":/entidades/jerryDead.png");
    setPixmap(sprites[8].scaledToHeight(70));

    isAlive = true;
    canMove = true;
    index = 0;
    limit = 1;
}

void player::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            sprites.push_back(image.copy((j*ancho_Jerry)+(bordeJerry+22)*(j+1),
            (i*alto_Jerry)+(bordeJerry+25)*(i+1), ancho_Jerry, alto_Jerry));
        }
    }
}

void player::cutSpritesDead(QString name)
{
    QPixmap image;
    image.load(name);

    spritesDead.push_back(image.copy(475, 0, 140, 150).scaledToHeight(30));
    spritesDead.push_back(image.copy(282, 0, 160, 150).scaledToHeight(30));
    spritesDead.push_back(image.copy(159, 0, 103, 150).scaledToHeight(30));
    spritesDead.push_back(image.copy(0, 0, 154, 150).scaledToHeight(30));
}

void player::setDirection(QPoint dir)
{
    tempDir = dir;
    if(dir == Right)
    {
        setPixmap(sprites[9].scaledToHeight(70));
        cursor = 9;
    }
    if(dir == Left)
    {
        setPixmap(sprites[3].scaledToHeight(70));
        cursor = 3;
    }
    if(dir == Up)
    {
        setPixmap(sprites[6].scaledToHeight(70));
        cursor = 6;
    }
    if(dir == Down)
    {
        setPixmap(sprites[0].scaledToHeight(70));
        cursor = 0;
    }
}

void player::switchAnimate()
{
    setPixmap(sprites[index+cursor].scaledToHeight(70));

    index += limit;
    if (index >= 2 || index <= 0)
        limit = -limit;
}

void player::animateDead()
{
    setPixmap(spritesDead[3]);
    //hide();
}

void player::isAnimate()
{
    //jerryMove->start();
}

void player::move(bool mover)
{
    if(mover == false) {
    direccion = tempDir;
    setPos(pos() + direccion * 4);
    switchAnimate();
    }

    else
    {
    if(direccion == Up) setPos(x(),y()+2);
    if(direccion == Down) setPos(x(),y()-2);
    if(direccion == Left) setPos(x()+2,y());
    if(direccion == Right) setPos(x()-2,y());

    }
}

void player::usarArma()
{

}

player::~player()
{

}



