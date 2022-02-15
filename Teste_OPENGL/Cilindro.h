//#include "C:/Users/Derley/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"
//
//typedef Eigen::Vector4d Vertice;
//typedef Eigen::Matrix4d Matrix;
//
//class Cilindro {
//public:
//    float raio;
//    float altura;
//    Vertice centro_base;
//    Vertice centro_top;
//    Vertice eixo;
//    Cilindro();
//    Cilindro(float raio, float altura, Vertice centro_base, Vertice eixo);
//    void aplicarTransformacao(Matrix transform);
//    void coordenadasDeCamera(Matrix mundoToCamera);
//    void colocarCoordenadasDeMundo(Matrix cameraToWorld);
//    Vertice planeIntersectBase(Vertice rayOrigin, Vertice rayDirection);
//    Vertice planeIntersectTop(Vertice rayOrigin, Vertice rayDirection);
//    Vertice normal(Vertice Ponto);
//
//    bool ValidatePonto(Vertice pint);
//    Vertice PrimeiraIntersecao(Vertice pP0, Vertice pVetor0);
//};
#pragma once
#include "Utils.h";

class Cilindro : public Shape
{
public:
    float raio;
    float altura;
    Ponto centro_base;
    Ponto centro_top;
    Ponto eixo;
    Cilindro();
    Cilindro(float raio, float altura, Ponto centro_base, Ponto eixo, Material mat);
    void aplicarTransformacao(Matriz transform);
    void coordenadasDeCamera(Matriz mundoToCamera);
    void colocarCoordenadasDeMundo(Matriz cameraToWorld);
    Ponto rayIntersect(Ponto rayOrigin, Ponto rayDirection);
    Ponto planeIntersectBase(Ponto rayOrigin, Ponto rayDirection);
    Ponto planeIntersectTop(Ponto rayOrigin, Ponto rayDirection);
    void  escalonamento(Ponto escalonamento);
    void  rotacao(Matriz rotacao);
    void  translacao(Ponto translacao);
    Ponto normal(Ponto ponto);
    bool valida(Ponto p);
    //Ponto* Bounds();
};