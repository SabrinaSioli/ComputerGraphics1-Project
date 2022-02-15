#include "Cilindro.h"

Cilindro::Cilindro() {};
Cilindro::Cilindro(float raio, float altura, Ponto centro_base, Ponto eixo, Material mat)
{
    this->raio = raio;
    this->altura = altura;
    this->centro_base = centro_base;
    this->centro_top = centro_base + eixo * altura;
    this->eixo = eixo;
    this->mat = mat;
};

/*Adicionar Vertice*/
void Cilindro::aplicarTransformacao(Matriz transform)
{
    Vertice cb = Vertice(this->centro_base[0], this->centro_base[1], this->centro_base[2], 1);
    cb = transform * cb;
    this->centro_base = Ponto(cb[0], cb[1], cb[2]);

    /*   Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
       eixov = transform * eixov;*/

       //this->eixo = Ponto(eixov[0], eixov[1], eixov[2]);
    this->centro_top = this->centro_base + this->eixo * this->altura;
};
/*Adicionar Vertice*/
void Cilindro::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice cb = Vertice(this->centro_base[0], this->centro_base[1], this->centro_base[2], 1);
    cb = mundoToCamera * cb;
    this->centro_base = Ponto(cb[0], cb[1], cb[2]);

    //Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
    //eixov = mundoToCamera * eixov;

    //this->eixo = Ponto(eixov[0], eixov[1], eixov[2]);
    this->centro_top = VerticeToPonto(mundoToCamera * PontoToVertice(this->centro_top));
};
/*Adicionar Vertice*/
void Cilindro::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice cb = Vertice(this->centro_base[0], this->centro_base[1], this->centro_base[2], 1);
    cb = cameraToWorld * cb;
    this->centro_base = Ponto(cb[0], cb[1], cb[2]);

    Vertice eixov = Vertice(this->eixo[0], this->eixo[1], this->eixo[2], 1);
    eixov = cameraToWorld * eixov;

    this->eixo = Ponto(eixov[0], eixov[1], eixov[2]);
    this->centro_top = this->centro_base + this->eixo * this->altura;
};

Ponto Cilindro::planeIntersectBase(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto v = this->centro_base - rayOrigin;
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
        return intersection;
    }
};

Ponto Cilindro::planeIntersectTop(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto v = this->centro_top - rayOrigin;
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

        return intersection;
    }
};

bool Cilindro::valida(Ponto p)
{
    Ponto pb = p - this->centro_base;
    float pi = pb.dot(this->eixo);

    return (0 <= pi && pi <= this->altura);
}

//Ponto* Cilindro::Bounds()
//{
//    Ponto max_bounds = this->centro_base + this->eixo * this->altura;
//    Ponto min_bounds = this->centro_base + this->eixo * this->altura;
//
//    Ponto p = Ponto(1, 0, 0);
//
//    if (this->eixo[1] != 1)
//    {
//        p = this->eixo.cross(Ponto(0, 1, 0));
//    }
//    Ponto p2 = p.cross(this->eixo);
//
//    for (int i = 0; i < 4; i++)
//    {
//        Ponto pb = this->centro_base + p * this->raio + p2 * this->raio;
//
//        if (pb[0] > max_bounds[0])
//        {
//            max_bounds[0] = pb[0];
//        }
//        if (pb[1] > max_bounds[1])
//        {
//            max_bounds[1] = pb[1];
//        }
//        if (pb[2] > max_bounds[2])
//        {
//            max_bounds[2] = pb[2];
//        }
//        if (pb[0] < min_bounds[0])
//        {
//            min_bounds[0] = pb[0];
//        }
//        if (pb[1] < min_bounds[1])
//        {
//            min_bounds[1] = pb[1];
//        }
//        if (pb[2] < min_bounds[2])
//        {
//            min_bounds[2] = pb[2];
//        }
//
//        Ponto pt = this->centro_top + p * this->raio - p2 * this->raio;
//
//        if (pt[0] > max_bounds[0])
//        {
//            max_bounds[0] = pt[0];
//        }
//        if (pt[1] > max_bounds[1])
//        {
//            max_bounds[1] = pt[1];
//        }
//        if (pt[2] > max_bounds[2])
//        {
//            max_bounds[2] = pt[2];
//        }
//
//        p = p2;
//        p2 = p.cross(this->eixo);
//    }
//
//    return new Ponto(min_bounds, max_bounds);
//}

Ponto Cilindro::rayIntersect(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto vetorNorm = rayDirection.normalized();

    Ponto C0P0 = rayOrigin - this->centro_base;

    Ponto v = C0P0 - (this->eixo * (C0P0.dot(this->eixo)));

    Ponto w = vetorNorm - (this->eixo * vetorNorm.dot(this->eixo));

    float a = w.dot(w);

    float b = v.dot(w);

    float c = v.dot(v) - this->raio * this->raio;

    float delta = b * b - a * c;

    if (delta < 0) {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }

    float t1, t2;
    float closest_distance = MAXFLOAT;

    Ponto int_base = planeIntersectBase(rayOrigin, rayDirection);
    if (int_base[0] < MAXFLOAT) {
        float d = sqrt(pow(int_base[0] - this->centro_base[0], 2) + pow(int_base[1] - this->centro_base[1], 2) + pow(int_base[2] - this->centro_base[2], 2));
        if (d > this->raio)
        {
            int_base = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
        else
        {
            closest_distance = sqrt(pow(int_base[0] - rayOrigin[0], 2) + pow(int_base[1] - rayOrigin[1], 2) + pow(int_base[2] - rayOrigin[2], 2));
        }
    }

    Ponto int_top = planeIntersectTop(rayOrigin, rayDirection);
    float d = sqrt(pow(int_top[0] - this->centro_top[0], 2) + pow(int_top[1] - this->centro_top[1], 2) + pow(int_top[2] - this->centro_top[2], 2));
    if (int_top[0] < MAXFLOAT && d <= this->raio) {
        float dist = sqrt(pow(rayOrigin[0] - int_top[0], 2) + pow(rayOrigin[1] - int_top[1], 2) + pow(rayOrigin[2] - int_top[2], 2));
        if (!(int_base[0] < MAXFLOAT) || dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_top;
        }
    }

    t1 = (-b + sqrt(delta)) / a;
    t2 = (-b - sqrt(delta)) / a;

    Ponto int_cyl1 = rayOrigin + vetorNorm.normalized() * t1;
    Ponto int_cyl2 = rayOrigin + vetorNorm.normalized() * t2;

    if (valida(int_cyl1))
    {
        double dist = sqrt(pow(rayOrigin[0] - int_cyl1[0], 2) + pow(rayOrigin[1] - int_cyl1[1], 2) + pow(rayOrigin[2] - int_cyl1[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl1;
        }
    }

    if (valida(int_cyl2))
    {
        double dist = sqrt(pow(rayOrigin[0] - int_cyl2[0], 2) + pow(rayOrigin[1] - int_cyl2[1], 2) + pow(rayOrigin[2] - int_cyl2[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl2;
        }
    }
    return int_base;
}


void Cilindro::escalonamento(Ponto escalonamento) // 0, 1, 1
{
    this->raio *= escalonamento[0];
    this->altura *= escalonamento[1];
    this->centro_top = this->centro_base + this->eixo * this->altura;
};

void Cilindro::rotacao(Matriz rotacao)
{
    this->centro_base = VerticeToPonto(rotacao * PontoToVertice(this->centro_base));
    this->eixo = VerticeToPonto(rotacao * PontoToVertice(this->eixo));
    this->centro_top = VerticeToPonto(rotacao * PontoToVertice(this->centro_top));
}
void Cilindro::translacao(Ponto translacao)
{
    this->centro_base += translacao;
    //this->eixo        = 
    this->centro_top += translacao;
}

Ponto Cilindro::normal(Ponto ponto)
{
    Ponto pontoToCenter = ponto - this->centro_base;
    float val = pontoToCenter.dot(this->eixo);
    Ponto a = this->eixo * val;

    Ponto v = this->centro_base + a;
    Ponto normal = ponto - v;
    normal = normal / this->raio;

    return normal;
}