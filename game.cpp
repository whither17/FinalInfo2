#include "game.h"

game::game()
{
    this->setWindowTitle("Nivel 2");
    scene = new QGraphicsScene;
    jerry = new player(scene);
    mantis = new enemy;

    healt[0] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));
    healt[1] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));
    healt[2] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));

    healt[0]->setScale(0.07);
    healt[1]->setScale(0.07);
    healt[2]->setScale(0.07);

    healt[0]->setPos(10*largo + 2, 20*largo + 10);
    healt[1]->setPos(9*largo + 2,20*largo + 10);
    healt[2]->setPos(8*largo + 2, 20*largo + 10);

    mode = Play;
    connect(jerry, SIGNAL(movement(int,int)), mantis, SLOT(distEnemy(int,int)));
    connect(mantis, SIGNAL(atac()), jerry, SLOT(damage()));
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
    mantis->setPos(-20, 100);
    scene->addItem(mantis);
    scene->addItem(jerry);
    scene->addRect(8*largo, 20*largo, 13*largo, 2*largo, QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(Qt::gray))->;

    scene->addItem(healt[0]);
    scene->addItem(healt[1]);
    scene->addItem(healt[2]);

    this->setScene(scene);
}

bool game::colliderLimits(player *pl)
{
    bool colision = false;
    for(int i = 0; i < 5; i++)
    {
        if(limites[i]->collidesWithItem(pl)) colision = true;
    }

    if((pl->x() > 780) || (pl->y() > 560) || (pl->x() < 0) || (pl->y() < 0)) colision = true;

    return colision;
}

void game::iniciarRonda()
{

}

void game::keyPressEvent(QKeyEvent *event)
{

    if (mode == Mode::Play) {

            if (event->key() == Qt::Key_W)
            {
                jerry->setDirection(Up);
                jerry->move(colliderLimits(jerry));
            }
            else if (event->key() == Qt::Key_S)
            {
                jerry->setDirection(Down);
                jerry->move(colliderLimits(jerry));
            }
            else if (event->key() == Qt::Key_A)
            {
                jerry->setDirection(Left);
                jerry->move(colliderLimits(jerry));
            }
            else if (event->key() == Qt::Key_D)
            {
                jerry->setDirection(Right);
                jerry->move(colliderLimits(jerry));
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

void game::uiManager()
{
    if(jerry->getLives() == 3)
    {
        healt[0]->show();
        healt[1]->show();
        healt[2]->show();
    }
    if(jerry->getLives() == 2)
    {
        healt[0]->hide();
        healt[1]->show();
        healt[2]->show();
    }
    if(jerry->getLives() == 1)
    {
        healt[0]->hide();
        healt[1]->hide();
        healt[2]->show();
    }
    if(jerry->getLives() == 0)
    {
        healt[0]->hide();
        healt[1]->hide();
        healt[2]->hide();

    }
}
