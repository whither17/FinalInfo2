#ifndef MACROS_H
#define MACROS_H
#include <QPoint>


const int largo = 27;
const int ancho = 27;
const int bordeJerry = 5;
const int alto_Jerry = 137;
const int ancho_Jerry = 103;

const int bordeMantis = 3;
const int alto_Mantis = 382;
const int ancho_Mantis = 252;


const QPoint Up = QPoint(0, -1);
const QPoint Down = QPoint(0, 1);
const QPoint Left = QPoint(-1, 0);
const QPoint Right = QPoint(1, 0);

const float ay = 9.8;  //ac g terrestre
const float vx0 = 40;   //velocidad
const float vy0 = 10;  //caida
const int distanciaTiro1 = 30;
#endif // MACROS_H
