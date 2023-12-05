#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QPixmap>
#include "nivel1/level1.h"
#include "nivel2/level2.h"
#include "nivel0/level0.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void cambiarWidget();
    void nivel1Open();
    ~MainWindow();

private slots:
    void irAnivel1();
    void irAnivel2();
    void tutorial();
    void restart();
    void restartLevel0();
    void cambiarNivel(int n_);
    void endGame();

private:
    Ui::MainWindow *ui;
    unsigned short ventana;
    level1 *nivel1;
    level2 *nivel2;
    level0 *nivel0;
};
#endif // MAINWINDOW_H
