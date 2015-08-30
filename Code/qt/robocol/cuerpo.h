#ifndef CUERPO_H
#define CUERPO_H

#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QPen>
#include "comunicacion.h"
#include <QTimer>

namespace Ui {
class cuerpo;
}

class cuerpo : public QWidget
{
    Q_OBJECT

public:
    explicit cuerpo(QWidget *parent = 0);
    void adelante();
    void atras();
    void parar();
    void girarDerecha();
    void girarIzquierda();
    ~cuerpo();
    bool oprimido;
    QTimer *espera;

private slots:
    void on_pushButton_clicked();
    void enviarDireccion();

private:
    Ui::cuerpo *ui;

    int x_plane;
    int y_plane;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* antena;
    info_puente_H motorSuperiorIsquierda;
    info_puente_H motorSuperiorDerecha;
    info_puente_H motorInferiorIsquierda;
    info_puente_H motorInferiorDerecha;

    int pwm1;
    int pwm2;
    int pwm3;
    int pwm4;
    QTimer *contador;



};

#endif // CUERPO_H
