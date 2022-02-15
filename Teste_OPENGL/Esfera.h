#pragma once
#include "Utils.h"

class Esfera : public Shape {
public:
    float raio;
    Ponto centro;
    Ponto rayIntersect(Ponto rayOrigin, Ponto rayDirection);
    Ponto normal(Ponto ponto);
    Esfera();
    Esfera(float raio, Ponto centro, Material mat);
    void  aplicarTransformacao(Matriz transform);
    void  coordenadasDeCamera(Matriz mundoToCamera);
    void  colocarCoordenadasDeMundo(Matriz cameraToWorld);
    void  escalonamento(Ponto escalonamento);
    void  rotacao(Matriz rotacao);
    void  translacao(Ponto translacao);
};