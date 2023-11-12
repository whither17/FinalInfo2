#include "game.h"

game::game()
{
    jerry = new player;
    scene = new QGraphicsScene;

}

void game::loadGame(QGraphicsView *n)
{
    n->setFrameStyle(0);
    n->setFixedSize(820, 600);
    scene->setBackgroundBrush(QBrush(QPixmap(":/fondos/calle.jpeg")));
    scene->setSceneRect(0,0,820,600);
    limites[0] = scene->addRect(0, 0, 4*largo, 6*ancho);
    limites[1] = scene->addRect(23*largo, 0, 8*largo, 6*ancho);
    limites[2] = scene->addRect(0, 20*ancho, 4*largo, 3*ancho);
    limites[3] = scene->addRect(23*largo, 20*ancho, 8*largo, 3*ancho);
    limites[4] = scene->addRect(19*largo, 0, 4*largo, 3*ancho);
    scene->addItem(jerry);
    n->setScene(scene);
}

void game::keyPressEvent(QKeyEvent *event)
{

}

game::~game()
{
    delete jerry;
}
