#include "liquid.h"

Liquid::Liquid(const QColor &target_color, const QColor &replacement_color, int position_id)
{
    this->target_color = target_color;
    this->replacement_color = replacement_color;
    this->position_id = position_id;
    QPixmap cc=selectpicture(position_id).copy();
    if(replacement_color!=none)
        change_pixmap_color(cc);
    this->Liquidbase=cc.copy();
}

void Liquid::change_pixmap_color(QPixmap &pixmap)
{
    QImage image = pixmap.toImage();

    //Itera pixel
    if(target_color!=none)
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            QColor pixel_color = image.pixelColor(x, y);
            if (pixel_color == target_color) {
                image.setPixelColor(x, y, replacement_color);
            }
        }
    }
    pixmap = QPixmap::fromImage(image);
}

int Liquid::getPosition_id() const
{
    return position_id;
}

QColor Liquid::getReplacement_color() const
{
    return replacement_color;
}


QPixmap Liquid::getLiquidbase() const
{
    return Liquidbase;
}

QPixmap Liquid::selectpicture(int id)
{
    if((id==3||id==2)&&replacement_color!=none){
        QPixmap Liquidbase(":/level1/textures/level1/botellarellena2o3.png");
        return Liquidbase;
    }else if(id==1&&replacement_color!=none){
        QPixmap Liquidbase(":/level1/textures/level1/botellarellena1.png");
        return Liquidbase;
    }else if(replacement_color==none){
        QPixmap Liquidbase(":/level1/textures/level1/vacio.png");
        return Liquidbase;
    }
}

bool Liquid::isitvoid()
{
    if(replacement_color==none){
        return true;
    }else
        return false;

}
