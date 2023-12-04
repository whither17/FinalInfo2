#include "level1.h"


level1::level1()
{
    this->setWindowTitle("Nivel 2");
    this->setWindowIcon(QIcon(":/logo/textures/win.jpeg"));
    this->setFrameStyle(0);
    this->setFixedSize(820, 600);
    scene= new QGraphicsScene;
    setScene(scene);
    QImage textura(":/level1/textures/level1/Font.png");
    QBrush fonti(textura);
    setBackgroundBrush(fonti);
    scene->setSceneRect(230,180,400,300);
    pp2=new pp(1,280,275);
    pp1=new pp(2,430,275);
    pp3=new pp(3,580,275);
    pp4=new pp(4,130,275);
    pp4->setPos(130,275);
    pocimas.push_back(pp2);
    pocimas.push_back(pp1);
    pocimas.push_back(pp3);
    pocimas.push_back(pp4);
    scene->addItem(pp2);
    scene->addItem(pp1);
    scene->addItem(pp3);
    scene->addItem(pp4);
    QObject::connect(pp2,SIGNAL(finrotacion()),this,SLOT(channgeLiquid()));
    QObject::connect(pp3,SIGNAL(finrotacion()),this,SLOT(channgeLiquid()));
    QObject::connect(pp4,SIGNAL(finrotacion()),this,SLOT(channgeLiquid()));
    QObject::connect(pp1,SIGNAL(finrotacion()),this,SLOT(channgeLiquid()));

}
level1::~level1()
{
    delete pp2;
    delete pp1;
    delete pp3;
    delete pp4;
    delete pp4;
    delete scene;
}

pp* level1::searchpp(int id)
{
    bool flag=false;
    pp *emisore;
    for(int i=0;i<pocimas.size();i++){
        if(pocimas[i]->getId()==id){
            emisore=pocimas[i];
            flag=true;
            break;
        }
    }
    if(flag)
    return emisore;
    else
    qDebug()<<"Out of Index";

}

void level1::secondanimation(int emisor, pp *receptor)
{
    emisore=searchpp(emisor);
    if(receptor->searchvoids()){
    emisore->setObjective(receptor->getX());
    emisore->onclik2();
    pocionreceptor=receptor->getId();
    }
    else{
        emisore->bottledance1();
    }

}

void level1::channgeLiquid()
{
    pp *vertiente,*vertido;
    vertiente=searchpp(pocionarriba);
    vertido=searchpp(pocionreceptor);
    Liquid *color=vertiente->emptyspace();
    vertido->fillspace(color);
    vertiente->returnToposition();
    movement_status=0;
    pocionarriba=-1;
    pocionreceptor=-1;


}

void level1::mousePressEvent(QMouseEvent *event)
{
    QRectF r1=colisiorect(pp4);
    QRectF r2=colisiorect(pp1);
    QRectF r3=colisiorect(pp2);
    QRectF r4=colisiorect(pp3);
 if (r1.contains((event->pos().rx()),(event->pos().y())))
    {
        if(movement_status==0){
        movement_status++;
        pocionarriba=4;
        pp4->onclik1();
        }else if(pocionarriba==4){
        pp4->returnToposition();
        movement_status=0;
        pocionarriba=-1;
        }else if (movement_status==1){
        secondanimation(pocionarriba,pp4);
        }
    }
    else if(r2.contains((event->pos().rx()),(event->pos().y())))
    {
        if(movement_status==0){
        movement_status++;
        pocionarriba=2;
        pp1->onclik1();
        }else if(pocionarriba==2){
        pp1->returnToposition();
        movement_status=0;
        pocionarriba=-1;
        }else if (movement_status==1){
        secondanimation(pocionarriba,pp1);
        }

    }
    else if(r3.contains((event->pos().rx()),(event->pos().y())))
    {
        if(movement_status==0){
        movement_status++;
        pocionarriba=1;
        pp2->onclik1();
        }else if(pocionarriba==1){
        pp2->returnToposition();
        movement_status=0;
        pocionarriba=-1;
        }else if (movement_status==1){
        secondanimation(pocionarriba,pp2);
        }
    }
    else if(r4.contains((event->pos().rx()),(event->pos().y())))
    {
        if(movement_status==0){
            movement_status++;
            pocionarriba=3;
            pp3->onclik1();
        }else if(pocionarriba==3){
            pp3->returnToposition();
            movement_status=0;
            pocionarriba=-1;
        }
        else if (movement_status==1){
            secondanimation(pocionarriba,pp3);
        }
    }

    QWidget::mousePressEvent(event);

}

QRectF level1::colisiorect(pp* base)
{
    QRectF colision(base->getX()-((base->getPicturefinal().width())*0.4)/2,base->getY()-((base->getPicturefinal().height())*0.4)/2,(base->getPicturefinal().width())*0.4,(base->getPicturefinal().height())*0.4);
    return colision;
}

