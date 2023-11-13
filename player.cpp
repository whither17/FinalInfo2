#include "player.h"

player::player()
{
    cutSprites(":/entidades/Jerry.png");
    setPixmap(sprites[8].scaledToHeight(70));
    jerryMove = new QTimer;
    jerryMove->setInterval(50);
    //connect(jerryMove, SIGNAL(timeout()), this, SLOT(switchAnimate()));
    isAlive = true;
    index = 0;
    limit = 1;

}

void player::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            sprites.push_back(image.copy((j*ancho_Jerry)+bordeJerry*(j+1),
            (i*alto_Jerry)+bordeJerry*(i+1), ancho_Jerry, alto_Jerry));
        }
    }
}

void player::setDirection(QPoint dir)
{
    tempDir = dir;
    if(dir == Right)
    {
        setPixmap(sprites[3].scaledToHeight(70));
        setRotation(120);
    }
}

void player::switchAnimate()
{
    if (isAlive)
    {
        setPixmap(sprites[index].scaledToHeight(70));
        index += limit;
        if (index >= 2 || index <= 0)
            limit = -limit;
    }
    else
    {

    }
}

void player::move()
{
    if(isAlive)
    {
        if(x() > 0 && x() < 820 && y() > 0 && y() < 600)
        {
            direccion = tempDir;
            setPos(pos()+direccion*2);
            jerryMove->start();
        }
    }
    //jerryMove->stop();
}

player::~player()
{

}



