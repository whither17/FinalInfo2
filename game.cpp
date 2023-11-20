#include "game.h"

game::game()
{
    this->setWindowTitle("Nivel 2");
    scene = new QGraphicsScene;
    jerry = new player(scene);
    rondaTimer = new QTimer;
    lag = new QTimer;
    round_n = 6;
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
    //connect(rondaTimer, SIGNAL(timeout()), this,SLOT(cargarEnemigos()));
    connect(rondaTimer, SIGNAL(timeout()), this, SLOT(uiManager()));
    connect(lag, SIGNAL(timeout()), this, SLOT(countDown()));

    loadDock();

    this->setScene(scene);

    mode = Play;
    amountOfEnemies = 0;
    killEnemies = 0;
    round = 1;
    rondaTimer->start();
    cargarEnemigos();
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

void game::loadDock()
{
    healt[0] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));
    healt[1] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));
    healt[2] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/corazon.png"));

    healt[0]->setScale(0.07);
    healt[1]->setScale(0.07);
    healt[2]->setScale(0.07);

    healt[0]->setPos(10*largo + 2, 20*largo + 10);
    healt[1]->setPos(9*largo + 2,20*largo + 10);
    healt[2]->setPos(8*largo + 2, 20*largo + 10);


    scene->addRect(8*largo, 20*largo, 13*largo, 2*largo, QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(Qt::gray));

    scene->addItem(healt[0]);
    scene->addItem(healt[1]);
    scene->addItem(healt[2]);

    t_puntos = new QGraphicsTextItem("Puntos: ");
    n_puntos = new QGraphicsTextItem("0");
    t_arma = new QGraphicsTextItem("Munición: ");
    n_municion = new QGraphicsTextItem(QString::number(jerry->getMunicion()));
    t_ronda = new QGraphicsTextItem("Ronda");
    n_ronda = new QGraphicsTextItem(QString::number(round));

    t_puntos->setDefaultTextColor(Qt::black);
    t_puntos->setFont(QFont("Joystix", 12));
    n_puntos->setDefaultTextColor(Qt::black);
    n_puntos->setFont(QFont("Joystix", 12));
    n_municion->setDefaultTextColor(Qt::black);
    n_municion->setFont(QFont("Joystix", 12));
    t_arma->setDefaultTextColor(Qt::black);
    t_arma->setFont(QFont("Joystix", 12));
    t_ronda->setDefaultTextColor(Qt::black);
    t_ronda->setFont(QFont("Joystix", 12));
    n_ronda->setDefaultTextColor(Qt::black);
    n_ronda->setFont(QFont("Joystix", 12));

    t_puntos->setPos(12*largo, 20*largo);
    n_puntos->setPos(15*largo, 20*largo);
    t_arma->setPos(12*largo, 21*largo);
    n_municion->setPos(15*largo,21*largo);
    t_ronda->setPos(18*largo,20*largo);
    n_ronda->setPos(20*largo,20*largo);

    scene->addItem(t_puntos);
    scene->addItem(n_puntos);
    scene->addItem(t_arma);
    scene->addItem(n_municion);
    scene->addItem(t_ronda);
    scene->addItem(n_ronda);
}

void game::win()
{
    qDebug() << "gano";
}

void game::cargarEnemigos()
{
    newMantis = new enemy[round_n];
    for(short i = 0; i < round_n; i++)
    {
    newMantis[i].setJerry(jerry);
    int distanceGeneration = 500;
    int angleOfGeneration = rand() % 360;

    int xPos = jerry->x() + distanceGeneration * std::cos(angleOfGeneration * M_PI / 180 +3);
    int yPos = jerry->y() + distanceGeneration * std::sin(angleOfGeneration * M_PI / 180 -2);

    xPos = qBound(0, xPos, static_cast<int>(scene->width()));
    yPos = qBound(0, yPos, static_cast<int>(scene->height()));


    newMantis[i].setPos(xPos, yPos);
    amountOfEnemies++;

    connect(jerry, SIGNAL(movement(int,int)), &newMantis[i], SLOT(distEnemy(int,int)));
    connect(&newMantis[i], SIGNAL(muerto()), jerry, SLOT(addScore()));
    connect(&newMantis[i], SIGNAL(muerto()), this, SLOT(remainingEnemies()));

    scene->addItem(&newMantis[i]);
    }
}

void game::remainingEnemies()
{
    killEnemies++;
    if(killEnemies >= round_n)
    {
        round++;
        delete []newMantis;
        wait(2.0);
        if(round < 4) cargarEnemigos();
    }
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
            if(mode == Mode::Play) jerry->usarArma();
        }

        else if(event->key() == Qt::Key_P){
            mode = Mode::Pause;
            pause();
        }
    }

    else if(mode == Mode::Pause){
        if(event->key() == Qt::Key_P){
            mode = Mode::Play;
            resume();
        }
    }
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
        jerry->dead();
    }

    n_puntos->setPlainText(QString::number(jerry->getScore()));
    n_municion->setPlainText(QString::number(jerry->getMunicion()));
    n_ronda->setPlainText(QString::number(round));
}

void game::roundManager()
{
    if(round == 1) round_n = 5;
    if(round == 2) round_n = 7;
    if(round == 3) round_n = 9;
    if(round == 4) win();
}

void game::wait(qreal msec) {
    if (mode != Mode::Play)
        return;
    mode = Mode::Pause;
    lag->start(int(1000 * msec));
}

void game::resume()
{
    jerry->play();
    for(short i = 0; i < round_n; i++)
    {
        newMantis[i].resume();
    }
}

void game::pause()
{

    jerry->pause();
    for(short i = 0; i < round_n; i++)
    {
        newMantis[i].pause();
    }
}

void game::countDown() {
    mode = Mode::Play;
    jerry->show();
    lag->stop();
    resume();
}

game::~game()
{
    //delete scene;
    delete jerry;
    delete t_puntos;
    delete t_arma;
    delete n_puntos;
    delete n_municion;
    delete n_ronda;
    delete t_ronda;

    delete healt[0];
    delete healt[1];
    delete healt[2];
}
