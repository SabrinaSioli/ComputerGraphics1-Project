#pragma once
#include "Utils.h"

class Cubo : public Shape
{
public:
    Cubo();
    Cubo(float side, Ponto  centro, Material mat);
    float side;
    float sidex;
    float sidey;
    float sidez;
    Ponto centro;
    Ponto v1;
    Ponto v2;
    Ponto v3;
    Ponto v4;
    Ponto v5;
    Ponto v6;
    Ponto v7;
    Ponto v8;
    Ponto vertices[8];
    Face faces[12];
    Ponto normal_intersect;
    void escalonamento(Ponto p);
    void Rotate(float angulo, Ponto eixo);
    void Translating(Ponto p);
    void Mirror(Ponto eixo);
    void coordenadasDeCamera(Matriz mundoToCamera);
    void colocarCoordenadasDeMundo(Matriz cameraToWorld);
    Ponto rayIntersect(Ponto rayOrigin, Ponto rayDirection);
    void setNormal(Ponto intersect);
    Ponto normal(Ponto ponto);
    //Ponto* Bounds();
    void atualizaFaces1();
    void atualizaFaces2();

    Matriz rotacaoX(float theta);
    Matriz rotacaoY(float theta);
    Matriz rotacaoZ(float theta);
    Matriz rotacao(Ponto eixo, float theta);


};