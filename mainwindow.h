#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QPixmap>
#include "ui_level1.h"
#include "ui_level2.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void cambiarWidget();
    ~MainWindow();

private slots:
    void irAnivel1();
    void irAnivel2();

private:
    Ui::MainWindow *ui;
    Ui::level1UI level1;
    Ui::level2UI level2;

    QWidget *nivel1Widget;
    QWidget *nivel2Widget;

    unsigned short ventana;
    game *nivel2;


};
#endif // MAINWINDOW_H
