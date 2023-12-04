#include "level0.h"

level0::level0(short level_) : level(level_)
{
    scene = new QGraphicsScene;
    text = new QGraphicsTextItem;
    this->setFrameStyle(0);
    this->setFixedSize(820, 600);
    this->setWindowTitle("Rick and Morty Love potion");
    this->setWindowIcon(QIcon(":/logo/textures/win.jpeg"));
    scene->setSceneRect(0,0,820,600);
    scene->addRect(largo, largo, 14*largo, 4*largo, QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(Qt::white));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Joystix", 18));
    text->setPos(2*largo, largo+largo/2);
    morty = new player(scene, ":/entidades/textures/level0/morty.png", 4, 14, 36, 200);
    setScene(scene);

    if(level == 1) loadLevel1();
    else if(level == 2) loadLevel2();
}

void level0::loadLevel1()
{
    scene->setBackgroundBrush(QBrush(QPixmap(":/fondos/textures/level0/garaje.jpg")));

    entidad = new QGraphicsPixmapItem(QPixmap(":/entidades/textures/level0/Rick.png").scaledToHeight(250));
    text->setPlainText("Dirigete donde Rick\npara hacer la pocion");
    morty->setPos(0,400);
    morty->setDirection(Right);
    morty->setTieneArma(false);
    entidad->setPos(600,300);
    scene->addItem(text);
    scene->addItem(entidad);
    scene->addItem(morty);
}

void level0::loadLevel2()
{
    scene->setBackgroundBrush(QBrush(QPixmap(":/fondos/textures/level0/parque.jpg")));
    entidad = new QGraphicsPixmapItem(QPixmap(":/entidades/textures/level0/chica.png").scaledToHeight(250));
    text->setPlainText("Usa la pocion en la chica");

    morty->setPos(0,400);
    morty->setDirection(Right);
    morty->setTieneArma(false);
    entidad->setPos(630,300);
    scene->addItem(text);
    scene->addItem(entidad);
    scene->addItem(morty);
    setScene(scene);
}

void level0::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
    {
        morty->setDirection(Left);
        morty->move(false);
    }
    else if (event->key() == Qt::Key_D)
    {
        morty->setDirection(Right);
        morty->move(false);
    }
    else if(event->key() == Qt::Key_Space)
    {
        if(morty->collidesWithItem(entidad))
        {
            if(level == 1)
            {
                irAnivel1();
            }
            else
            {
                transformacion();
            }
        }
    }
}

void level0::irAnivel1()
{
    emit irNivel(1);
    delete this;
}

void level0::irAnivel2()
{
    emit irNivel(2);
    delete this;
}

void level0::transformacion()
{
    entidad->setPixmap(QPixmap(":/entidades/textures/level0/Mantis_Traitor.png"));
    QElapsedTimer timer;

    timer.start();
    qint64 duration = 3000;

    while (timer.elapsed() < duration)
    {

        QCoreApplication::processEvents();
    }
    irAnivel2();
}
