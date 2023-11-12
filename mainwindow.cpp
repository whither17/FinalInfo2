#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
        nivel1Widget(0),                          //inicializamos miembro a miembro los componentes de UI
        nivel2Widget(0),
        ui(new Ui::MainWindow)
{
    nivel1Widget = new QWidget(parent); //creamos los widgets
    nivel2Widget = new QWidget(parent);
    level1.setupUi(nivel1Widget);     //creamos las instancias
    level2.setupUi(nivel2Widget);

    ui->setupUi(this);
    this->setFixedSize(600, 400);
    this->setWindowTitle("Rick and Morty Love potion");
    ui->label->setFixedSize(400, 100);
    ventana = 0;

    connect(ui->botonN1, SIGNAL(clicked(bool)), this, SLOT(irAnivel1()));
    connect(ui->botonN2, SIGNAL(clicked(bool)), this, SLOT(irAnivel2()));

    nivel2 = new game;
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

void MainWindow::cambiarWidget()
{
    switch (ventana) {
    case 1:
        nivel1Widget->setFixedSize(800, 600);
        nivel1Widget->setVisible(true);
        nivel2Widget->setVisible(false);
        this->setVisible(false);
        break;
    case 2:
        nivel2Widget->setFixedSize(820, 600);
        nivel1Widget->setVisible(false);
        nivel2Widget->setVisible(true);
        this->setVisible(false);
        nivel2->loadGame(level2.graphicsView);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nivel2;
    delete nivel1Widget;
    delete nivel2Widget;

}

