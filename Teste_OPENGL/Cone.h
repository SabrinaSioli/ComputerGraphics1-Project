#pragma once
#include "Utils.h"

class Cone : public Shape
{
public:
    float raio;
    float altura;
    Ponto centro;
    Ponto eixo;
    Ponto origin;
    Cone();
    Cone(float raio, float altura, Ponto centro, Ponto eixo, Material mat);
    void  aplicarTransformacao(Matriz transform);
    void  coordenadasDeCamera(Matriz mundoToCamera);
    void  colocarCoordenadasDeMundo(Matriz cameraToWorld);
    Ponto rayIntersect(Ponto rayOrigin, Ponto rayDirection);
    Ponto planeIntersectBase(Ponto rayOrigin, Ponto rayDirection);
    Ponto normal(Ponto ponto);
    void  escalonamento(Ponto escalonamento);
    void  rotacao(Matriz rotacao);
    void  translacao(Ponto translacao);
    bool  valida(Ponto p, Ponto ray);
    Ponto intersecao_base(Ponto rayOrigin, Ponto rayDirection);
    //Ponto* Bounds();
};