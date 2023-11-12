#include "player.h"

player::player()
{
    cutSprites(":/entidades/Jerry.png");
    setPixmap(sprites[8]);
}

void player::cutSprites(QString name)
{
    QPixmap image;
    image.load(name);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            sprites.push_back(image.copy((i*ancho_Jerry)+5*i+1,(j*alto_Jerry)+5*j+1, ancho_Jerry, alto_Jerry));
        }
    }
}

player::~player()
{

}
