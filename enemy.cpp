#include "enemy.h"

enemy::enemy(player *jerr) : jerry(jerr)
{
    cutSprites(":/entidades/Mantis.png");
    setPixmap(spritesRight[7].scaledToHeight(110));

    animateTimer = new QTimer;

    animateTimer->setInterval(70);

    animateTimer->start();

    connect(animateTimer, SIGNAL(timeout()), this, SLOT(switchAnimate()));
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(checkCollitions()));

    setDirection(Left);
    index = 0;
    limit = 1;
    healt = 100;
    speed = rand() %3+2;
}

void enemy::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    for(int i = 0; i < 8; i++)
    {
        spritesRight.push_back(image.copy((i*ancho_Mantis)+(bordeMantis)*(i+1),
        (bordeMantis), ancho_Mantis, alto_Mantis));
    }


    for(int j = 7; j >= 0; j--)
    {
        spritesLeft.push_back(image.copy((j*ancho_Mantis)+(bordeMantis)*(j+1),
        (alto_Mantis)+(bordeMantis)*(2), ancho_Mantis, alto_Mantis));
    }
}

void enemy::setDirection(QPoint dir)
{
    tempDir = dir;
}

void enemy::attack()
{

}

void enemy::distEnemy(int x_, int y_)
{
    int dx = x_ - x();
    int dy = y_ - y();

    if (abs(dx) > abs(dy)) {
        if (dx > 0) {

            setDirection(Right);
        } else {
            setDirection(Left);
        }
    } else {

        if (dy > 0) {
            setDirection(Up);

        } else {
            setDirection(Down);
        }
    }

    if(abs(dx) < 5 && abs(dy) < 5) attack();
}

void enemy::checkCollitions()
{
    collitions = collidingItems();
    for(int i = 0; i < collitions.length(); i++)
    {
        if(typeid(*(collitions[i])) == typeid(bala))
        {
            if(jerry->getTipo_arma() == 1)
            {
                healt -=50;
                b1 = jerry->getBala();
                b1->parar_tiro();
            }
            else
            {
                healt = 0;
                b1 = jerry->getBala();
                b1->parar_tiro();
            }


        }
        if(healt <= 0) die();
    }
}

void enemy::switchAnimate()
{
    index += limit;

    if (index > 7)
    {
        limit = 1;
        index = 0;
    }

    if(tempDir == Right || tempDir == Up || tempDir == Down)
    {
        setPixmap(spritesRight[index].scaledToHeight(110));

    }
    else if (tempDir == Left)
    {
        setPixmap(spritesLeft[index].scaledToHeight(110));

    }

}

void enemy::move()
{
    if(tempDir == Left) setPos(x() - speed, y());

    else if(tempDir == Right) setPos(x() + speed, y());

    else if(tempDir == Up) setPos(x(), y() + speed);

    else setPos(x(), y() - speed);

}

void enemy::die()
{
    emit muerto();
    animateTimer->stop();
    hide();
}





