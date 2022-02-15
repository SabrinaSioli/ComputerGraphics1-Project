#include "Esfera.h"

Esfera::Esfera() {};
Esfera::Esfera(float raio, Ponto centro, Material mat)
{
    this->raio = raio;
    this->centro = centro;
    this->mat = mat;
};

Ponto Esfera::rayIntersect(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto pV0N = rayDirection.normalized();
    Ponto C0P0 = rayOrigin - centro;
    double a = pV0N.dot(pV0N);
    double b = pV0N.dot(C0P0);
    double c = C0P0.dot(C0P0) - this->raio * this->raio;
    double delta = b * b - a * c;

    if (delta > 0) {
        double t1 = (-b + sqrt(delta)) / a;
        double t2 = (-b - sqrt(delta)) / a;
        Ponto intersection1 = (rayOrigin + pV0N * t1);
        Ponto intersection2 = (rayOrigin + pV0N * t2);
        double distance1 = sqrt(pow(intersection1[0] - rayOrigin[0], 2) + pow(intersection1[1] - rayOrigin[1], 2) + pow(intersection1[2] - rayOrigin[2], 2));
        double distance2 = sqrt(pow(intersection2[0] - rayOrigin[0], 2) + pow(intersection2[1] - rayOrigin[1], 2) + pow(intersection2[2] - rayOrigin[2], 2));
        Ponto intersection = (distance1 < distance2) ? intersection1 : intersection2;
        return intersection;
    }
    else if (delta == 0) {
        double t1 = (-b + sqrt(delta)) / a;
        Ponto intersection = (rayOrigin + pV0N * t1);
        return intersection;
    }
    else {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
};

Ponto Esfera::normal(Ponto ponto)
{
    Ponto normal = (ponto - this->centro).normalized();
    return normal;
};

void Esfera::aplicarTransformacao(Matriz transform)
{
    Vertice c = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    c = transform * c;
    this->centro = Ponto(c[0], c[1], c[2]);
}

void Esfera::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice c = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    c = mundoToCamera * c;
    this->centro = Ponto(c[0], c[1], c[2]);
}

void Esfera::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice c = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    c = cameraToWorld * c;
    this->centro = Ponto(c[0], c[1], c[2]);
}


void Esfera::escalonamento(Ponto escalonamento) // 0, 1, 1
{
    this->raio *= escalonamento[0];
};

void Esfera::rotacao(Matriz rotacao)
{
    this->centro = VerticeToPonto(rotacao * PontoToVertice(this->centro));
};

void Esfera::translacao(Ponto translacao) {
    this->centro += translacao;
}

//Ponto* Esfera::Bounds() {
//    Ponto max_bounds = Ponto(this->centro[0] + this->raio, this->centro[1] + this->raio, this->centro[2] + this->raio);
//    Ponto min_bounds = Ponto(this->centro[0] - this->raio, this->centro[1] - this->raio, this->centro[2] - this->raio);
//
//    return new Ponto(min_bounds, max_bounds);
//};