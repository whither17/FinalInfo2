#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QPixmap>
#include "level2.h"

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
    unsigned short ventana;
    level2 *nivel2;
};
#endif // MAINWINDOW_H
