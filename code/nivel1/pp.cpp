#include "pp.h"
// Green =1;
//Pink==2;
//Yellow==3;

pp::pp(int id, int x, int y)
{
    this->id = id;
    this->x=x;
    this->originalX=x;
    this->originalY=y;
    this->y=y;
    cuerpo=new bottle(1,x,y);
    if(id==1){
        l1= new Liquid(target_color,green,1);
        l2= new Liquid(target_color,pink,2);
        l3= new Liquid(target_color,yellow,3);
        QPixmap li1= l1->getLiquidbase().copy();
        QPixmap li2= l2->getLiquidbase().copy();
        QPixmap li3= l3->getLiquidbase().copy();

        QPixmap body=cuerpo->getBorder_bottle().copy();
        QPixmap final1=combinePixmaps(body,li1,3);
        QPixmap final2=combinePixmaps(final1,li2,2);
        QPixmap final3=combinePixmaps(final2,li3,1);
        setScale(0.4);
        setPixmap(final3);
        setPos(x,y);
        posiciones.push_back(l1);
        posiciones.push_back(l2);
        posiciones.push_back(l3);
        this->picturefinal=final3;
    }else if(id==2){
        l1= new Liquid(target_color,yellow,1);
        l2= new Liquid(target_color,pink,2);
        l3= new Liquid(target_color,green,3);
        QPixmap li1= l1->getLiquidbase().copy();
        QPixmap li2= l2->getLiquidbase().copy();
        QPixmap li3= l3->getLiquidbase().copy();
        QPixmap body=cuerpo->getBorder_bottle().copy();
        QPixmap final1=combinePixmaps(body,li1,3);
        QPixmap final2=combinePixmaps(final1,li2,2);
        QPixmap final3=combinePixmaps(final2,li3,1);
        posiciones.push_back(l1);
        posiciones.push_back(l2);
        posiciones.push_back(l3);
        setScale(0.4);
        setPixmap(final3);
        setPos(x,y);
         this->picturefinal=final3;
    }else if(id==3){
        l1= new Liquid(target_color,pink,1);
        l2= new Liquid(target_color,green,2);
        l3= new Liquid(target_color,none,3);
        QPixmap li1= l1->getLiquidbase().copy();
        QPixmap li2= l2->getLiquidbase().copy();
        QPixmap li3= l3->getLiquidbase().copy();
        QPixmap body=cuerpo->getBorder_bottle().copy();
        QPixmap final1=combinePixmaps(body,li1,3);
        QPixmap final2=combinePixmaps(final1,li2,2);
        QPixmap final3=combinePixmaps(final2,li3,1);
        posiciones.push_back(l1);
        posiciones.push_back(l2);
        posiciones.push_back(l3);
        setScale(0.4);
        setPixmap(final3);
        setPos(x,y);
         this->picturefinal=final3;

    }else if(id==4){
        l1= new Liquid(target_color,yellow,1);
        l2= new Liquid(target_color,none,2);
        l3= new Liquid(target_color,none,3);
        QPixmap li1= l1->getLiquidbase().copy();
        QPixmap li2= l2->getLiquidbase().copy();
        QPixmap li3= l3->getLiquidbase().copy();
        QPixmap body=cuerpo->getBorder_bottle().copy();
        QPixmap final1=combinePixmaps(body,li1,3);
        QPixmap final2=combinePixmaps(final1,li2,2);
        QPixmap final3=combinePixmaps(final2,li3,1);
        posiciones.push_back(l1);
        posiciones.push_back(l2);
        posiciones.push_back(l3);
        setScale(0.4);
        setPixmap(final3);
        setPos(x,y);
        this->picturefinal=final3;

    }
    setTransformOriginPoint(((getPicturefinal().width())*0.4)/2,((getPicturefinal().height())*0.4)/2);
}

QPixmap pp::combinePixmaps(const QPixmap &pixmap1, const QPixmap &pixmap2,int idi)
{
    float newy,newx;
    if(idi==1){newy=0;newx=4;}else if(idi==2){newy=150;newx=4;}else if(idi==3){newy=299;newx=2;}
    QPixmap combinedPixmap(pixmap1.size());
    combinedPixmap.fill(Qt::transparent);
    QPainter painter(&combinedPixmap);
    painter.drawPixmap(0, 0, pixmap1);
    painter.drawPixmap(newx, newy, pixmap2);
    painter.end();
    return combinedPixmap;
}

bool pp::searchvoids()
{
    bool voi=false;
    for(int i=0;i<posiciones.size();i++){
        if(posiciones[i]->isitvoid()){
            voi=true;
            break;
        }
    }
    return voi;
}

int pp::getId() const
{
    return id;
}

void pp::fillspace(Liquid *nuevoL)
{
    for(int i=0;i<posiciones.size();i++){
        if(posiciones[i]->isitvoid()){
            qDebug()<<posiciones[i]->getPosition_id();
            posiciones[i]=new Liquid(target_color,nuevoL->getReplacement_color(),i+1);
            updatepixmap();
            break;
        }
    }

}

Liquid *pp::emptyspace()
{

    Liquid* nn=l1+1;
    for( int i=posiciones.size()-1;i>=0;i--){
        if(!(posiciones[i]->isitvoid())){
            nn=posiciones[i];
            posiciones[i]=new Liquid(target_color,none,i);
            updatepixmap();
            break;
        }
    }

    if(nn==l1+1){
        qDebug()<<"B A S U R A";}
    return nn;
}

void pp::onclik1()
{
    crono= new QTimer(this);
    crono->start(80);
    connect(crono, &QTimer::timeout, this, &pp::firstStateofmovement);

}

void pp::onclik2()
{
    if(this->getX()<objective){
         movement=true;
    }else{
         objective=objective+10;
         movement=false;}
    crono2= new QTimer(this);
    crono2->start(80);
    connect(crono2, &QTimer::timeout, this, &pp::secondStateofmovement);

}

void pp::bottledance2()
{
    if(danceid<4){
    danceid++;
    crono2=new QTimer(this);
    crono2->start(15);
    connect(crono2, &QTimer::timeout, this, &pp::acelerationmovement2);
    }else{
    danceid=0;
    }
}

void pp::bottledance1()
{

    if(danceid<4){
         cr3=new QTimer(this);
         cr3->start(15);
         connect(cr3, &QTimer::timeout, this, &pp::acelerationmovement);
    }else
         danceid=0;
}


void pp::firstStateofmovement()
{
    setPos(x,y-10);
    this->y=y-10;
    if(getY()<150){
      crono->stop();
      delete crono;
    }
}

void pp::secondStateofmovement()
{
    if(movement){
    setPos(x+10,y);
    this->x=x+10;
    if(getX()>objective){
      crono2->stop();
            delete crono2;
      rotatePixmap(1);
    }
    }else{
    setPos(x-10,y);
    this->x=x-10;
    if(getX()-20<objective){
      crono2->stop();
      delete crono2;
      rotatePixmap(0);
    }
    }

}

void pp::rotation()
{
    setRotation(angle);
    if(angle<-89){
    crono->stop();
    delete crono;
    emit finrotacion();
    angle=0;
    }
    angle-=10;
}

void pp::rotation2()
{
    setRotation(angle);
    if(angle>89){
    crono->stop();
    delete crono;
    angle=0;
    emit finrotacion();
    }
    angle+=10;

}

void pp::acelerationmovement()
{
    setPos(x+4,y);
    this->x=x+4;
    if(getX()>originalX+12){
    cr3->stop();
    delete cr3;
    bottledance2();
    }
}

void pp::acelerationmovement2()
{
    setPos(x-4,y);
    this->x=x-4;
    if(getX()<originalX-12){
    crono2->stop();
    delete crono2;
    bottledance1();
    }
}

void pp::backtoposition()
{
    if(!(x==originalX&&y==originalY)){
    if(x>originalX){
    x=x-10;
    }
    if(y>originalY){
    y=y-10;
    }if(x<originalX){
    x=x+10;
    }if(y<originalY){
    y=y+10;
    }
    }else if(x==originalX&&y==originalY){
        setRotation(0);
        delete crono;
    }
    setPos(x,y);
}
int pp::getY()
{
    return y;
}

int pp::getX()
{
    return x;
}


QPixmap pp::getPicturefinal() const
{
    return picturefinal;
}

void pp::setObjective(int newObjective)
{
    this->objective = newObjective;
}

void pp::updatepixmap()
{
    QPixmap body=cuerpo->getBorder_bottle().copy();
    QPixmap final1=combinePixmaps(body,posiciones[0]->getLiquidbase(),3);
    QPixmap final2=combinePixmaps(final1,posiciones[1]->getLiquidbase(),2);
    QPixmap final3=combinePixmaps(final2,posiciones[2]->getLiquidbase(),1);
    setScale(0.4);
    setPixmap(final3);
    setPos(x,y);
    this->picturefinal=final3;
}

void pp::returnToposition()
{
    crono= new QTimer(this);
    crono->start(20);
    connect(crono, &QTimer::timeout, this, &pp::backtoposition);
}

void pp::rotatePixmap(int control)
{
    if (control==0){
    crono= new QTimer(this);
    crono->start(40);
    connect(crono, &QTimer::timeout, this, &pp::rotation);}
    else if(control==1){
    crono= new QTimer(this);
    crono->start(40);
    connect(crono, &QTimer::timeout, this, &pp::rotation2);
    }
}

