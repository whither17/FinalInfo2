#include "enemy.h"

enemy::enemy()
{
    cutSprites(":/entidades/Mantis.png");
    setPixmap(sprites[0].scaledToHeight(110));

    animateTimer = new QTimer;

    animateTimer->setInterval(65);

    animateTimer->start(100);

    connect(animateTimer, SIGNAL(timeout()), this, SLOT(switchAnimate()));
    index = 0;
    limit = 1;
    tempDir = Left;
}

void enemy::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            sprites.push_back(image.copy((j*ancho_Mantis)+(bordeMantis)*(j+1),
            (i*alto_Mantis)+(bordeMantis)*(i+1), ancho_Mantis, alto_Mantis));
        }
    }
}

void enemy::setDirection(QPoint dir)
{
    tempDir = dir;
    if(dir == Right)
    {
        setPixmap(sprites[0].scaledToHeight(110));
        cursor = 0;
    }
    if(dir == Left)
    {
        setPixmap(sprites[8].scaledToHeight(110));
        cursor = 0;
        index = 15;
        limit = -1;
    }
}

void enemy::switchAnimate()
{
    setPixmap(sprites[index+cursor].scaledToHeight(110));

    index += limit;
    qDebug() << index;


    if(tempDir == Right)
    {
        if (index > 7)
        {
            limit = 1;
            index = 0;
        }
    }
    else if (tempDir == Left)
    {
        if (index < 8)
        {
            limit = -1;
            index = 15;
        }
    }

}




