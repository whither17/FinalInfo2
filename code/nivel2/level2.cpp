#include "level2.h"

level2::level2()
{
    this->setWindowTitle("Nivel 2");
    this->setWindowIcon(QIcon(":/logo/textures/win.jpeg"));
    scene = new QGraphicsScene;
    jerry = new player(scene, ":/entidades/textures/level2/Jerry.png", 5, 22, 25, 70);
    jerry->setTieneArma(true);
    rondaTimer = new QTimer;
    timer = new QElapsedTimer;
    sound = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    sound->setAudioOutput(audioOutput);
    sound->setSource(QUrl("qrc:/level2/sound/levelUP.mp3"));
    audioOutput->setVolume(60);
}

void level2::loadlevel2()
{
    this->setFrameStyle(0);
    this->setFixedSize(820, 600);
    scene->setBackgroundBrush(QBrush(QPixmap(":/fondos/textures/level2/calle.jpeg")));
    scene->setSceneRect(0,0,820,600);

    //cajas de colisiones objetos del fondo
    limites[0] = scene->addRect(0, 0, 4*largo, 6*ancho);               //sup izq
    limites[1] = scene->addRect(23*largo, 0, 8*largo, 6*ancho);        //sup der
    limites[2] = scene->addRect(0, 20*ancho, 4*largo, 3*ancho);        //inf izq
    limites[3] = scene->addRect(23*largo, 20*ancho, 8*largo, 3*ancho); //inf der
    limites[4] = scene->addRect(19*largo, 0, 4*largo, 3*ancho);        //arbol

    for(short i = 0; i < 5; i++)
    {
        limites[i]->setVisible(false);
    }

    jerry->setPos(13*ancho, 13*largo);
    scene->addItem(jerry);
    rondaTimer->start();
    connect(rondaTimer, SIGNAL(timeout()), this, SLOT(uiManager()));
    connect(jerry, SIGNAL(fail()), this, SLOT(gameFail()));

    loadDock();

    this->setScene(scene);

    mode = Play;
    killEnemies = 0;
    round = 0;
    round_n = 0;
    jerry->setDirection(Left);
    jerry->setTipo_arma(1);
    remainingEnemies();
}

bool level2::colliderLimits(player *pl)
{
    bool colision = false;
    for(int i = 0; i < 5; i++)
    {
        if(limites[i]->collidesWithItem(pl)) colision = true;
    }

    if((pl->x() > 780) || (pl->y() > 560) || (pl->x() < 0) || (pl->y() < 0)) colision = true;

    return colision;
}

void level2::loadDock()
{
    healt[0] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/textures/level2/corazon.png"));
    healt[1] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/textures/level2/corazon.png"));
    healt[2] = new QGraphicsPixmapItem(QPixmap(":/Ui_level2/textures/level2/corazon.png"));

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

void level2::win()
{
    emit winer();
}

void level2::cargarEnemigos()
{
    int xPos = 0;
    int yPos = 0;
    int distanceGeneration = 0;
    int angleOfGeneration = 0;

    for(short i = 0; i <= round_n; i++)
    {
        newMantis = new enemy;
        newMantis->setJerry(jerry);
        distanceGeneration = 480;
        angleOfGeneration = rand() % 360;

        xPos = jerry->x() + distanceGeneration * std::cos(angleOfGeneration * M_PI / 180 +3);
        yPos = jerry->y() + distanceGeneration * std::sin(angleOfGeneration * M_PI / 180 -2);
        if(i % 2 == 0) newMantis->setPos(xPos, -1*yPos);
        else if(i % 3 == 0 && i != 6) newMantis->setPos(xPos + 2, yPos);

        else newMantis->setPos(xPos, yPos+10);

        connect(jerry, SIGNAL(movement(int,int)), newMantis, SLOT(distEnemy(int,int)));
        connect(newMantis, SIGNAL(atac()), jerry, SLOT(damage()));
        connect(newMantis, SIGNAL(Drop(int,int)), this, SLOT(generateDrop(int,int)));
        connect(newMantis, SIGNAL(muerto()), jerry, SLOT(addScore()));
        connect(newMantis, SIGNAL(muerto()), this, SLOT(remainingEnemies()));
        connect(this, SIGNAL(kill()), newMantis, SLOT(eliminar()));
        connect(this, SIGNAL(pausar()), newMantis, SLOT(pause()));
        connect(this, SIGNAL(reanudar()), newMantis, SLOT(resume()));

        scene->addItem(newMantis);
    }
}

void level2::remainingEnemies()
{
    killEnemies++;

    if(killEnemies >= round_n)
    {
        round++;
        sound->play();

        roundManager();
        if(round < 4)
        {
            emit kill();
            cargarEnemigos();
        }
        killEnemies = 0;
    }
}

void level2::keyPressEvent(QKeyEvent *event)
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
            else if(event->key() == Qt::Key_1)
            {
                jerry->setTipo_arma(1);
            }
            else if(event->key() == Qt::Key_2)
            {
                jerry->setTipo_arma(2);
            }

        else if (event->key() == Qt::Key_Space)
        {
            if(mode == Mode::Play)
            {
                jerry->usarArma();
            }
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

void level2::uiManager()
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

void level2::roundManager()
{
    if(round == 1) round_n = 5;
    if(round == 2) round_n = 7;
    if(round == 3) round_n = 9;
    if(round == 4) win();
}

void level2::waitDead(qreal msec)
{
    timer->start();
    qint64 duration = msec*1000;

    while (timer->elapsed() < duration)
    {
        jerry->dead();
        QCoreApplication::processEvents();
    }
}

void level2::wait(qreal msec)
{
    timer->start();
    qint64 duration = msec*1000;

    while (timer->elapsed() < duration)
    {
        QCoreApplication::processEvents();
    }
    jerry->setDirection(Left);
}

void level2::resume()
{
    jerry->play();
    emit reanudar();
}

void level2::pause()
{
    jerry->pause();
    emit pausar();
}

void level2::generateDrop(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(1, 2);

    int random_number = distribution(gen);
    it = new item(random_number);
    it->setPos(x, y);
    connect(it, SIGNAL(power(int)), jerry, SLOT(powerUp(int)));
    scene->addItem(it);
}

void level2::gameFail()
{
    pause();
    jerry->setScore(0);
    jerry->restartArma();
    round = 1;
    killEnemies = 0;
    waitDead(5);
    jerry->setPos(13*ancho, 13*largo);
    jerry->setIsAlive(true);
    jerry->setLives(3);
    emit kill();
    wait(3);
    cargarEnemigos();
    jerry->play();
}

level2::~level2()
{
    delete jerry;
    delete t_puntos;
    delete t_arma;
    delete n_puntos;
    delete n_municion;
    delete n_ronda;
    delete t_ronda;
    delete sound;
    delete healt[0];
    delete healt[1];
    delete healt[2];
    delete timer;
}
