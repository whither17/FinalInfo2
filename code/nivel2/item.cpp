#include "item.h"

item::item(int tipo_)
{
    tipo = tipo_;
    if(tipo == 1)
    cutSprites(":/entidades/textures/level2/pocion.png");
    else cutSprites(":/entidades/textures/level2/municion.png");
    uso = true;
    live = new QTimer;
    sound = new QMediaPlayer;
    audioOutput = new QAudioOutput;

    audioOutput->setVolume(10);

    sound->setAudioOutput(audioOutput);
    sound->setSource(QUrl("qrc:/level2/sound/drop.mp3"));
    live->start();
    connect(live, SIGNAL(timeout()), this, SLOT(checkCollitions()));

}

void item::cutSprites(QString name)
{
    if(tipo == 1)
    {
        setPixmap(QPixmap(name).scaledToHeight(25));
    }
    else
    {
        setPixmap(QPixmap(name).scaledToHeight(25));
    }
}

int item::getTipo() const
{
    return tipo;
}

item::~item()
{
    delete live;
    delete sound;
    delete audioOutput;
}

void item::checkCollitions()
{
    if(uso)
    {
        collitions = collidingItems();
        for(int i = 0; i < collitions.length(); i++)
        {
            if(typeid(*(collitions[i])) == typeid(player))
            {
                uso = false;
                emit power(tipo);
                sound->play();
            }
        }
    }
    else delete this;
}
