#include "item.h"

item::item(int tipo_)
{
    tipo = tipo_;
    if(tipo == 1)
    cutSprites(":/entidades/pocion.png");
    else cutSprites(":/entidades/municion.png");
    uso = true;
    live = new QTimer;
    sound = new QMediaPlayer;
    audioOutput = new QAudioOutput;

    audioOutput->setVolume(10);

    sound->setAudioOutput(audioOutput);
    sound->setSource(QUrl("qrc:/level2/drop.mp3"));
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
                if(sound->isPlaying() == false)
                {
                    delete sound;
                    delete audioOutput;
                }
            }
        }
    }
    else delete this;
}
