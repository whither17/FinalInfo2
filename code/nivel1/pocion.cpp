#include "pocion.h"

Pocion::Pocion(const QColor &target_color, const QColor &replacement_color, int id, int x, int y)
{
    x=1;
}
    /*this->target_color = target_color;
    this->replacement_color = replacement_color;
    this->id = id;
    cuerpo=new bottle(1,x,y);
    l1= new Liquid(target_color,replacement_color,1,x,y);
    l2= new Liquid(target_color,replacement_color,2,x,y);
    l3= new Liquid(target_color,replacement_color,3,x,y);
    //printall();
}
*/
/*void pocion::printall()
{
    QPixmap body=cuerpo->getBorder_bottle();
    QPixmap li1= l1->getLiquidbase();
    QPixmap li2= l2->getLiquidbase();
    QPixmap li3= l3->getLiquidbase();
    //const QPixmap final1=combinePixmaps(body,li1);
    setScale(0.4);
    setPixmap(body);
    setPos(x,y);

}
*/
/*QPixmap pocion::combinePixmaps(const QPixmap &pixmap1, const QPixmap &pixmap2)
{
    QPixmap combinedPixmap(pixmap1.size());
    QPainter painter(&combinedPixmap);
    painter.drawPixmap(0, 0, pixmap1);
    painter.drawPixmap(0, 0, pixmap2);
    painter.end();
    return combinedPixmap;
}

*/
