#include "player.h"

player::player(QGraphicsScene *scene)
{
    cutSprites(":/entidades/Jerry.png");
    cutSpritesDead(":/entidades/jerryDead.png");
    setPixmap(sprites[8].scaledToHeight(70));

    JerryMove = new QTimer;
    sound = new QMediaPlayer;
    audioOutput = new QAudioOutput;

    JerryMove->start();

    connect(JerryMove, SIGNAL(timeout()), this, SLOT(posicionActual()));

    scena = scene;

    isAlive = true;
    canMove = true;

    lives = 3;
    index = 0;
    limit = 1;
    score = 0;
    tipo_arma = 1;

    arma1 = new arma(1, scena);
    arma2 = new arma(2, scena);

    cambiarArma(tipo_arma);

    municion1 = arma1->getMunicion();
    municion2 = arma2->getMunicion();

    sound->setAudioOutput(audioOutput);
    sound->setSource(QUrl("qrc:/level2/damage.mp3"));
    qDebug() << sound->hasAudio();
    audioOutput->setVolume(60);
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
    if(isAlive)
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

        arma1->setDirection(dir);
        arma2->setDirection(dir);
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

void player::posicionActual()
{
    if(isAlive)
    emit movement(x(), y());
}

void player::addScore()
{
    score += 100;
}

void player::damage()
{
    lives = lives - 1;
    audioOutput->setVolume(50);
    sound->play();

    if(lives <= 0)
    {
        lives = 0;
        emit fail();
    }
}

void player::powerUp(int a)
{
    if(a == 1)
    {
        if(lives == 3) score += 50;
        else lives = lives + 1;
    }
    else
    {
        if(tipo_arma == 1) arma1->setMunicion(arma1->getMunicion() + 15);

        if(tipo_arma == 2) arma2->setMunicion(arma2->getMunicion() + 10);
    }
}

void player::setIsAlive(bool newIsAlive)
{
    isAlive = newIsAlive;
}

void player::restartArma()
{

}

void player::setLives(short newLives)
{
    lives = newLives;
}

void player::setScore(int newScore)
{
    score = newScore;
}

int player::getScore() const
{
    return score;
}

int player::getTipo_arma() const
{
    return tipo_arma;
}

void player::setTipo_arma(int newTipo_arma)
{
    tipo_arma = newTipo_arma;
    cambiarArma(tipo_arma);
}

QPoint player::getTempDir() const
{
    return tempDir;
}

int player::getMunicion() const
{
    if(tipo_arma == 1) return arma1->getMunicion();
    if(tipo_arma == 2) return arma2->getMunicion();
}

bala *player::getBala()
{
    if(tipo_arma == 1) return arma1->getBala();
    if(tipo_arma == 2) return arma2->getBala();
}

short player::getLives() const
{
    return lives;
}

void player::move(bool mover)
{
    if(isAlive)
    {
        if(mover == false) {
            direccion = tempDir;
            setPos(pos() + direccion * 4);
            switchAnimate();
        }

        else
        {
            if(direccion == Up) setPos(x(), y() + 2);
            if(direccion == Down) setPos(x(), y() - 2);
            if(direccion == Left) setPos(x() + 2, y());
            if(direccion == Right) setPos(x() - 2, y());
        }

        if(tipo_arma == 1) arma1->mover(x(), y());
        if(tipo_arma == 2) arma2->mover(x(), y());
    }
}

void player::cambiarArma(int tipo)
{
    tipo_arma = tipo;
    if(tipo_arma == 1)
    {
        arma1->mover(-50, -50);
        scena->addItem(arma1);
        arma1->show();
        arma2->hide();
    }
    else
    {
        arma2->mover(-50, -50);
        scena->addItem(arma2);
        arma2->show();
        arma1->hide();
    }
}

void player::usarArma()
{
    if(isAlive)
    {
        if(tipo_arma == 1) arma1->disparar();
        else arma2->disparar();
    }
}

void player::dead()
{
    animateDead();
    isAlive = false;
}

void player::play()
{
    JerryMove->start();
}

void player::pause()
{
    JerryMove->stop();
}

player::~player()
{
    delete arma1;
    delete arma2;
    delete JerryMove;
}



