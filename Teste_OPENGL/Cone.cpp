#include "Cone.h"

Cone::Cone() {};
Cone::Cone(float raio, float altura, Ponto centro, Ponto eixo, Material mat)
{
    this->raio = raio;
    this->altura = altura;
    this->centro = centro;
    this->eixo = eixo;
    this->origin = centro + eixo * altura;
    this->mat = mat;
};

//Utilizar Vertice
void Cone::aplicarTransformacao(Matriz transform)
{
    Vertice cb = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    cb = transform * cb;
    this->centro = Ponto(cb[0], cb[1], cb[2]);

    Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
    eixov = transform * eixov;

    this->origin = this->centro + this->eixo * this->altura;
};
//Utilizar Vertice
void Cone::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice cb = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    cb = mundoToCamera * cb;
    this->centro = Ponto(cb[0], cb[1], cb[2]);

    Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
    eixov = mundoToCamera * eixov;

    this->origin = this->centro + this->eixo * this->altura;
};
//Utilizar Vertice
void Cone::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice cb = Vertice(this->centro[0], this->centro[1], this->centro[2], 1);
    cb = cameraToWorld * cb;
    this->centro = Ponto(cb[0], cb[1], cb[2]);

    Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
    eixov = cameraToWorld * eixov;

    this->origin = this->centro + this->eixo * this->altura;
};

Ponto Cone::planeIntersectBase(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto v = this->centro - rayOrigin;
    float p = this->eixo.dot(v);
    float t = this->eixo.dot(rayDirection);

    if (t == 0)
    {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Ponto intersection = rayOrigin + rayDirection * s;
        intersection[3] = 1;
        return intersection;
    }
};

bool Cone::valida(Ponto p, Ponto ray)
{
    Ponto aux = p - ray;
    float s = aux.dot(this->eixo);

    return ((s >= 0) && (s <= this->altura));
}

Ponto Cone::intersecao_base(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto v = this->centro - rayOrigin;
    float p = this->eixo.dot(v);
    float t = this->eixo.dot(rayDirection);

    if (t == 0)
    {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Ponto intersection = rayOrigin + rayDirection * s;

        float d = sqrt(pow(intersection[0] - this->centro[0], 2) + pow(intersection[1] - this->centro[1], 2) + pow(intersection[2] - this->centro[2], 2));

        if (d <= this->raio)
        {
            return intersection;
        }
        else
        {
            return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
    }


}

void Cone::escalonamento(Ponto escalonamento) // 0, 1, 1
{
    this->raio *= escalonamento[0];
    this->altura *= escalonamento[1];
    this->origin = this->centro + this->eixo * this->altura;
};

void Cone::rotacao(Matriz rotacao)
{
    this->centro = VerticeToPonto(rotacao * PontoToVertice(this->centro));
    this->eixo = VerticeToPonto(rotacao * PontoToVertice(this->eixo));
    this->origin = VerticeToPonto(rotacao * PontoToVertice(this->origin));
}

void Cone::translacao(Ponto translacao)
{
    this->centro += translacao;
    //this->eixo   += translacao;
    this->origin += translacao;
}

//Ponto* Cone::Bounds()
//{
//    Ponto max_bounds = this->centro + this->altura * this->eixo;
//    Ponto min_bounds = this->centro - this->altura * this->eixo;
//
//    Ponto p = Ponto(1, 0, 0);
//
//    if (this->eixo[1] != 1)
//    {
//        p = this->eixo * Ponto(0, 1, 0);
//    }
//    Ponto p2 = (this->eixo).cross(p);
//
//    for (int i = 0; i < 4; i++)
//    {
//        if (this->centro[0] > max_bounds[0])
//        {
//            max_bounds[0] = this->centro[0];
//        }
//        if (this->centro[0] < min_bounds[0])
//        {
//            min_bounds[0] = this->centro[0];
//        }
//        if (this->centro[1] > max_bounds[1])
//        {
//            max_bounds[1] = this->centro[1];
//        }
//        if (this->centro[1] < min_bounds[1])
//        {
//            min_bounds[1] = this->centro[1];
//        }
//        if (this->centro[2] > max_bounds[2])
//        {
//            max_bounds[2] = this->centro[2];
//        }
//        if (this->centro[2] < min_bounds[2])
//        {
//            min_bounds[2] = this->centro[2];
//        }
//
//        p = p2;
//        p2 = (this->eixo).cross(p);
//    }
//
//    return new Ponto(min_bounds, max_bounds);
//}

Ponto Cone::rayIntersect(Ponto rayOrigin, Ponto rayDirection)
{
    float cos_theta = this->altura / sqrt(pow(this->altura, 2) + pow(this->raio, 2));

    Ponto normal_aux = this->eixo * this->altura;

    Ponto Vertice = this->centro + normal_aux;

    Ponto d = rayDirection.normalized();

    Ponto v = Vertice - rayOrigin;

    float a = pow(d.dot(this->eixo), 2) - (d.dot(d) * pow(cos_theta, 2));

    float b = d.dot(v) * pow(cos_theta, 2) - ((d.dot(this->eixo) * v.dot(this->eixo)));

    float c = pow(v.dot(this->eixo), 2) - (pow(cos_theta, 2) * v.dot(v));

    float delta = b * b - (a * c);

    float t1, t2;
    Ponto pi = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if (delta > 0)
    {
        if (a != 0)
        {
            t1 = (-b + sqrt(delta)) / a;
            t2 = (-b - sqrt(delta)) / a;
        }
        else
        {
            t1 = -c / (2 * b);
            t2 = -c / (2 * b);
        }

        Ponto p1 = rayOrigin + d * t1;
        Ponto p2 = rayOrigin + d * t2;

        Ponto bi = intersecao_base(rayOrigin, d);
        if (valida(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }

        float d1 = MAXFLOAT;
        if (pi[0] < MAXFLOAT)
        {
            d1 = sqrt(pow(pi[0] - rayOrigin[0], 2) + pow(pi[1] - rayOrigin[1], 2) + pow(pi[2] - rayOrigin[2], 2));
        }

        float d2 = sqrt(pow(p2[0] - rayOrigin[0], 2) + pow(p2[1] - rayOrigin[1], 2) + pow(p2[2] - rayOrigin[2], 2));
        if (valida(this->origin, p2))
        {
            if (!(pi[0] < MAXFLOAT) || d2 < d1)
            {
                pi = p2;
            }

        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }
    }
    else if (delta == 0 && b != 0 && a != 0)
    {
        t1 = -b + sqrt(delta) / a;
        Ponto p1 = rayOrigin + d * t1;
        Ponto bi = intersecao_base(rayOrigin, d);
        float db = sqrt(pow(bi[0] - rayOrigin[0], 2) + pow(bi[1] - rayOrigin[1], 2) + pow(bi[2] - rayOrigin[2], 2));
        float dp = sqrt(pow(p1[0] - rayOrigin[0], 2) + pow(p1[1] - rayOrigin[1], 2) + pow(p1[2] - rayOrigin[2], 2));
        if (valida(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT && (!(pi[0] < MAXFLOAT) || db < dp))
        {
            pi = bi;
        }
    }
    return pi;
};

Ponto Cone::normal(Ponto ponto)
{
    Ponto v = this->altura * this->eixo;
    Ponto n = this->centro + v;
    Ponto a = ponto - this->centro;

    float f = a.dot(this->eixo);
    Ponto p = this->centro + f * this->eixo;

    Ponto a2 = ponto - p;
    Ponto a3 = n - ponto;

    Ponto T = a2.cross(a3);
    Ponto N = (a3.cross(T)).normalized();

    return N;

};