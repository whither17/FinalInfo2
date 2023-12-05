#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 370);
    this->setWindowTitle("Rick and Morty Love potion");
    this->setWindowIcon(QIcon(":/logo/textures/win.jpeg"));
    ui->label->setFixedSize(400, 100);
    ui->boton_atras->hide();
    ventana = 0;

    connect(ui->botonN1, SIGNAL(clicked(bool)), this, SLOT(irAnivel1()));
    connect(ui->botonN2, SIGNAL(clicked(bool)), this, SLOT(irAnivel2()));
    connect(ui->botonTut, SIGNAL(clicked(bool)), this, SLOT(tutorial()));
    connect(ui->boton_atras, SIGNAL(clicked(bool)), this, SLOT(restart()));
}

void MainWindow::irAnivel1()
{
    ventana = 1;
    this->cambiarWidget();
}

void MainWindow::irAnivel2()
{
    ventana = 2;
    this->cambiarWidget();
}

void MainWindow::tutorial()
{
    this->setFixedSize(1050, 600);
    this->setWindowTitle("Instrucciones");
    ui->boton_atras->setGeometry(this->width() - ui->boton_atras->width() - 10, this->height() - ui->boton_atras->height() - 23, ui->boton_atras->width(), ui->boton_atras->height());
    ui->boton_atras->show();
    ui->groupBox->hide();
    ui->im_instrucciones->setGeometry(0,0, 1050, 550);
    ui->im_instrucciones->setPixmap(QPixmap(":/logo/textures/instrucciones.png").scaledToHeight(600));
    ui->im_instrucciones->show();
}

void MainWindow::restart()
{
    this->show();
    this->setFixedSize(600, 370);
    this->setWindowTitle("Rick and Morty Love potion");
    ui->label->setFixedSize(400, 100);
    ui->boton_atras->hide();
    ui->im_instrucciones->hide();
    ui->groupBox->show();
    ventana = 0;
}

void MainWindow::restartLevel0()
{
    nivel1->hide();
    nivel0 = new level0(2);
    connect(nivel0, SIGNAL(irNivel(int)), this, SLOT(cambiarNivel(int)));
    nivel0->show();
}

void MainWindow::cambiarNivel(int n_)
{
    if(n_ == 1) nivel1Open();
    if(n_ == 2)
    {
        nivel2 = new level2;
        nivel2->loadlevel2();
        connect(nivel2, SIGNAL(winer()), this, SLOT(endGame()));
        nivel2->show();
    }
}

void MainWindow::nivel1Open()
{
    nivel0->hide();
    nivel1 = new level1;
    connect(nivel1, SIGNAL(Endgame()), this, SLOT(restartLevel0()));
    nivel1->show();
}

void MainWindow::endGame()
{
    this->show();
    ui->im_instrucciones->setGeometry(0,0, 600, 340);
    ui->im_instrucciones->setPixmap(QPixmap(":/logo/textures/win.jpeg").scaledToHeight(600));

    this->setFixedSize(600, 400);
    this->setWindowTitle("Win!");
    ui->boton_atras->setGeometry(this->width() - ui->boton_atras->width() - 10, this->height() - ui->boton_atras->height() - 23, ui->boton_atras->width(), ui->boton_atras->height());
    ui->groupBox->hide();
    ui->im_instrucciones->show();
    ui->boton_atras->show();
    delete nivel2;
}


void MainWindow::cambiarWidget()
{
    switch (ventana) {
    case 1:
        this->setVisible(false);
        nivel0 = new level0(1);
        connect(nivel0, SIGNAL(irNivel(int)), this, SLOT(cambiarNivel(int)));
        nivel0->show();
        break;
    case 2:
        this->setVisible(false);
        nivel2 = new level2;
        nivel2->loadlevel2();
        connect(nivel2, SIGNAL(winer()), this, SLOT(endGame()));
        nivel2->show();
        break;        
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    //delete ui;
}

