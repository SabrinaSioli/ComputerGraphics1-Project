#pragma once
#include "eigen-3.4.0/Eigen/Dense"


#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <limits>

#define ALTURA 500
#define LARGURA 500
#define BG Ponto(0, 0, 0)

#define MAXFLOAT 10000000.f

using namespace std;

typedef Eigen::Vector3f Ponto;
typedef Eigen::Vector4f Vertice;
typedef Eigen::Matrix4f Matriz;

class Material
{
public:
    float shininess;
    Ponto ka;
    Ponto kd;
    Ponto ks;
    Material();
    Material(Ponto ka, Ponto kd, Ponto ks, float shininess);
};

class Shape
{
public:
    virtual void coordenadasDeCamera(Matriz mundoToCamera) = 0;
    virtual void colocarCoordenadasDeMundo(Matriz cameraToWorld) = 0;
    virtual Ponto rayIntersect(Ponto rayOrigin, Ponto rayDirection) = 0;
    virtual Ponto normal(Ponto ponto) = 0;
    //virtual Ponto Bounds() = 0;
    Material mat;
};

Vertice PontoToVertice(Ponto p);

Ponto VerticeToPonto(Vertice p);

class Face {
public:
    Face();
    Face(Ponto v1, Ponto v2, Ponto v3);
    Ponto v1;
    Ponto v2;
    Ponto v1v2;
    Ponto v1v3;
    Ponto v2v3;
    Ponto v3v1;
    Ponto v3;
    Ponto normal;
    Ponto intersecaoNoPlano(Ponto rayOrigin, Ponto rayDirection);
    Ponto rayCasting(Ponto rayOrigin, Ponto rayDirection);
    void  coordenadasDeCamera(Matriz mundoToCamera);
    Ponto getNormal();
};

// ============================ ILUMINAÇÃO ==============================
class Iluminacao {
public:
    float r;
    float g;
    float b;
    virtual float fatorDifuso(Ponto ponto,  Ponto normal) = 0;
    virtual float fatorEspecular(Ponto ponto,  Ponto normal) = 0;
    virtual Ponto difuseIntensity(Ponto ponto,  Ponto normal, Material mat) = 0;
    virtual Ponto specularIntensity(Ponto ponto,  Ponto normal, Material mat) = 0;
    virtual void coordenadasDeCamera(Matriz mundoToCamera) = 0;
    virtual void colocarCoordenadasDeMundo(Matriz cameraToWorld) = 0;
    Iluminacao();
};

class IluminacaoAmbiente
{
public:
    float r;
    float g;
    float b;
    IluminacaoAmbiente();
    Ponto ambientIntensity(Ponto ponto,  Material mat);
    IluminacaoAmbiente(float r, float g, float b);
};

class SpotIluminacao : public Iluminacao
{
public:
    Ponto posicao;
    Ponto direcao;
    float angulo;
    SpotIluminacao(float r, float g, float b, Ponto posicao, Ponto direcao, float angulo);
    float fatorDifuso(Ponto ponto,  Ponto normal);
    float fatorEspecular(Ponto ponto,  Ponto normal);
    Ponto difuseIntensity(Ponto ponto,  Ponto normal, Material mat);
    Ponto specularIntensity(Ponto ponto,  Ponto normal, Material mat);
    void coordenadasDeCamera(Matriz mundoToCamera);
    void colocarCoordenadasDeMundo(Matriz cameraToWorld);
};

class FarIluminacao : public Iluminacao
{
public:
    Ponto direcao;
    FarIluminacao(float r, float g, float b, Ponto direcao);
    float fatorDifuso(Ponto ponto,  Ponto normal);
    float fatorEspecular(Ponto ponto,  Ponto normal);
    Ponto difuseIntensity(Ponto ponto,  Ponto normal, Material mat);
    Ponto specularIntensity(Ponto ponto,  Ponto normal, Material mat);
    void coordenadasDeCamera(Matriz mundoToCamera);
    void colocarCoordenadasDeMundo(Matriz cameraToWorld);
};

class PontoLighting : public Iluminacao
{
public:
    Ponto posicao;
    PontoLighting(float r, float g, float b, Ponto posicao);
    float fatorDifuso(Ponto ponto,  Ponto normal);
    float fatorEspecular(Ponto ponto,  Ponto normal);
    Ponto difuseIntensity(Ponto ponto,  Ponto normal, Material mat);
    Ponto specularIntensity(Ponto ponto,  Ponto normal, Material mat);
    void coordenadasDeCamera(Matriz mundoToCamera);
    void colocarCoordenadasDeMundo(Matriz cameraToWorld);
};