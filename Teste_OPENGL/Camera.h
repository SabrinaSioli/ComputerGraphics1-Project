#pragma once
#include "Utils.h"

class Camera {
public:
    Ponto eye;
    Ponto lookAt;
    Ponto viewUp;
    Ponto k;
    Ponto i;
    Ponto j;
    double d;
    double plano_tamanho;
    Camera();
    Camera(Ponto eye, Ponto lookAt, Ponto viewUp, int d, int plano_tamanho);
    Matriz mundoToCamera();
    Matriz cameraToWorld();
    void atualiza();
    void moverX(float x); //n sei se eu uso
    void moverY(float y);
    void moverZ(float z);
    void moverPara(Ponto eye);
};