#include "game.h"

game::game()
{
    this->setWindowTitle("Nivel 2");
    jerry = new player;
    scene = new QGraphicsScene;
    mode = Play;
}

void game::loadGame()
{
    this->setFrameStyle(0);
    this->setFixedSize(820, 600);
    scene->setBackgroundBrush(QBrush(QPixmap(":/fondos/calle.jpeg")));
    scene->setSceneRect(0,0,820,600);
    //cajas de colisiones objetos del fondo
    limites[0] = scene->addRect(0, 0, 4*largo, 6*ancho);               //sup izq
    limites[1] = scene->addRect(23*largo, 0, 8*largo, 6*ancho);        //sup der
    limites[2] = scene->addRect(0, 20*ancho, 4*largo, 3*ancho);        //inf izq
    limites[3] = scene->addRect(23*largo, 20*ancho, 8*largo, 3*ancho); //inf der
    limites[4] = scene->addRect(19*largo, 0, 4*largo, 3*ancho);        //arbol
    jerry->setPos(13*ancho, 13*largo);

    scene->addItem(jerry);
    this->setScene(scene);
}

void game::colliderLimits(player *pl)
{
    for(int i = 0; i < 5; i++)
    {
        if(limites[i]->collidesWithItem(pl)) pl->setCanMove(false);
        //break;
    }
}

void game::keyPressEvent(QKeyEvent *event)
{

    if (mode == Mode::Play) {
        if (event->key() == Qt::Key_W)
        {
            jerry->setDirection(Up);
            colliderLimits(jerry);
            jerry->move();
        }
        else if (event->key() == Qt::Key_S)
        {
            jerry->setDirection(Down);
            colliderLimits(jerry);
            jerry->move();
        }
        else if (event->key() == Qt::Key_A)
        {
            jerry->setDirection(Left);
            colliderLimits(jerry);
            jerry->move();
        }
        else if (event->key() == Qt::Key_D)
        {
            jerry->setDirection(Right);
            colliderLimits(jerry);
            jerry->move();
        }
        else if (event->key() == Qt::Key_Space)
        {
            jerry->usarArma();
        }
        else if(event->key() == Qt::Key_P){
            mode = Mode::Pause;
            //pause();
            //background->fadeIn();
            //get_ready->setPlainText("GAME PAUSE");
        }
    }
    else if(mode == Mode::Pause){
        if(event->key() == Qt::Key_P){
            mode = Mode::Play;
            //resume();
            //background->fadeOut();
            //get_ready->setPlainText("");
            //pause->play();
        }
    }
}

game::~game()
{
    //delete scene;
    delete jerry;
}
