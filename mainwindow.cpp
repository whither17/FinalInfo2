#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
        ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(600, 400);
    this->setWindowTitle("Rick and Morty Love potion");
    ui->label->setFixedSize(400, 100);
    ventana = 0;

    connect(ui->botonN1, SIGNAL(clicked(bool)), this, SLOT(irAnivel1()));
    connect(ui->botonN2, SIGNAL(clicked(bool)), this, SLOT(irAnivel2()));


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
        this->setVisible(false);
        break;
    case 2:

        this->setVisible(false);
        nivel2 = new level2;
        nivel2->loadlevel2();
        nivel2->show();
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nivel2;
}

