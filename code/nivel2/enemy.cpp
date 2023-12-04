#include "enemy.h"

enemy::enemy()
{
    cutSprites(":/entidades/textures/level2/Mantis.png");
    setPixmap(spritesRight[7].scaledToHeight(95));

    animateTimer = new QTimer;

    soundDead = new QMediaPlayer;
    soundDamage = new QMediaPlayer;
    audioOutput1 = new QAudioOutput;
    audioOutput2 = new QAudioOutput;
    audioOutput1->setVolume(10);
    audioOutput2->setVolume(10);
    soundDead->setAudioOutput(audioOutput1);
    soundDamage->setAudioOutput(audioOutput2);
    soundDead->setSource(QUrl("qrc:/level2/sound/mantisDead.mp3"));
    soundDamage->setSource(QUrl("qrc:/level2/sound/mantisDamage.mp3"));

    animateTimer->setInterval(70);
    animateTimer->start();

    connect(animateTimer, SIGNAL(timeout()), this, SLOT(switchAnimate()));
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(animateTimer, SIGNAL(timeout()), this, SLOT(checkCollitions()));

    setDirection(Left);
    index = 0;
    limit = 1;
    healt = 100;
    int drop = rand() %100;
    if(drop > 70) isDrop = true;
    else isDrop = false;
    speed = rand() %3+2;
    isAlive = true;
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

void enemy::distEnemy(int x_, int y_)
{
    if(isAlive)
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
    }
}

void enemy::checkCollitions()
{
    if(isAlive)
    {
        collitions = collidingItems();
        for(int i = 0; i < collitions.length(); i++)
        {
            if(typeid(*(collitions[i])) == typeid(bala))
            {
                if(jerry->getTipo_arma() == 1)
                {
                    healt -=50;
                    if(healt >= 50) soundDamage->play();
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
        setPixmap(spritesRight[index].scaledToHeight(95));

    }

    else if (tempDir == Left)
    {
        setPixmap(spritesLeft[index].scaledToHeight(95));

    }
}

void enemy::move()
{
    if(tempDir == Left) setPos(x() - speed, y());

    else if(tempDir == Right) setPos(x() + speed, y());

    else if(tempDir == Up) setPos(x(), y() + speed);

    else setPos(x(), y() - speed);

    if(collidesWithItem(jerry))
    {
        emit atac();
        if(jerry->getIsAlive()) wait(1);
    }
}

void enemy::wait(qreal msec)
{
    timer.start();
    qint64 duration = msec*1000;

    while (timer.elapsed() < duration)
    {
        animateTimer->stop();
        QCoreApplication::processEvents();
    }
    animateTimer->start();
}

void enemy::die()
{
    if(isAlive)
    {
        emit muerto();
        soundDead->play();
        if(isDrop) emit Drop(x(), y());
        isAlive = false;
    }
    animateTimer->stop();
    //hide();
    //delete this;
}

void enemy::setJerry(player *newJerry)
{
    jerry = newJerry;
}

void enemy::resume()
{
    if(isAlive)
    {
        animateTimer->start();
    }
}

void enemy::pause()
{
    animateTimer->stop();
}

/*
enemy::~enemy()
{
    delete animateTimer;
    delete soundDead;
    delete soundDamage;
    delete audioOutput1;
    delete audioOutput2;
}
*/
