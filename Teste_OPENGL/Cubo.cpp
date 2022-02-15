#include "Cubo.h"

Cubo::Cubo() {};
Cubo::Cubo(float side, Ponto  centro, Material mat)
{
    this->side = side;
    this->centro = centro;
    this->mat = mat;

    sidex = side;
    sidey = side;
    sidez = side;

    float sx = this->sidex / 2;
    float sy = this->sidey / 2;
    float sz = this->sidez / 2;
    //int t = 100;
    this->vertices[0] = Ponto(this->centro[0] - sx, this->centro[1] + sy, this->centro[2] + sz);
    this->vertices[1] = Ponto(this->centro[0] - sx, this->centro[1] + sy, this->centro[2] - sz);
    this->vertices[2] = Ponto(this->centro[0] + sx, this->centro[1] + sy, this->centro[2] - sz);
    this->vertices[3] = Ponto(this->centro[0] + sx, this->centro[1] + sy, this->centro[2] + sz);
    this->vertices[4] = Ponto(this->centro[0] - sx, this->centro[1] - sy, this->centro[2] + sz);
    this->vertices[5] = Ponto(this->centro[0] - sx, this->centro[1] - sy, this->centro[2] - sz);
    this->vertices[6] = Ponto(this->centro[0] + sx, this->centro[1] - sy, this->centro[2] - sz);
    this->vertices[7] = Ponto(this->centro[0] + sx, this->centro[1] - sy, this->centro[2] + sz);


    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);

    this->normal_intersect = Ponto(0, 0, 0);
}

void Cubo::atualizaFaces1()
{
    float sx = this->sidex / 2;
    float sy = this->sidey / 2;
    float sz = this->sidez / 2;
    //int t = 100;
    this->vertices[0] = Ponto(this->centro[0] - sx, this->centro[1] + sy, this->centro[2] + sz);
    this->vertices[1] = Ponto(this->centro[0] - sx, this->centro[1] + sy, this->centro[2] - sz);
    this->vertices[2] = Ponto(this->centro[0] + sx, this->centro[1] + sy, this->centro[2] - sz);
    this->vertices[3] = Ponto(this->centro[0] + sx, this->centro[1] + sy, this->centro[2] + sz);
    this->vertices[4] = Ponto(this->centro[0] - sx, this->centro[1] - sy, this->centro[2] + sz);
    this->vertices[5] = Ponto(this->centro[0] - sx, this->centro[1] - sy, this->centro[2] - sz);
    this->vertices[6] = Ponto(this->centro[0] + sx, this->centro[1] - sy, this->centro[2] - sz);
    this->vertices[7] = Ponto(this->centro[0] + sx, this->centro[1] - sy, this->centro[2] + sz);


    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);

    //this->normal_intersect = Ponto(0, 0, 0);
}

void Cubo::atualizaFaces2() {
    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);
}



void Cubo::escalonamento(Ponto p)
{
    sidex *= p[0];
    sidey *= p[1];
    sidez *= p[2];

    atualizaFaces1();
}

//Utilizar Vertice
void Cubo::Rotate(float angulo, Ponto eixo)
{
    Matriz Rx = rotacaoX(angulo);
    Matriz Ry = rotacaoY(angulo);
    Matriz Rz = rotacaoZ(angulo);

    Matriz transform;

    for (int i = 0; i < 3; i++) {
        if (i == 0 && eixo[0] > 0) {
            transform = Rx;
        }
        else if (i == 1 && eixo[1] > 0) {
            transform = Ry;
        }
        else if (i == 2 && eixo[2] > 0) {
            transform = Rz;
        }
        else {
            continue;
        }

        Vertice aux_centro = Vertice(centro[0], centro[1], centro[2], 1);

        aux_centro = transform * aux_centro;
        centro[0] = aux_centro[0];
        centro[1] = aux_centro[1];
        centro[2] = aux_centro[2];

        for (int i = 0; i < 8; i++)
        {
            Vertice v = Vertice(this->vertices[i][0], this->vertices[i][1], this->vertices[i][2], 1);
            Vertice p = transform * v;
            this->vertices[i] = Ponto(p[0], p[1], p[2]);
        }

        atualizaFaces2();
    }
}

void Cubo::Translating(Ponto p) {
    
    for (int i = 0; i < 8; i++) {
        this->vertices[i] += p;
    }
    centro = centro + p;
    atualizaFaces2();

}
void Cubo::Mirror(Ponto eixo)
{
}
//Utilizar Vertice

void Cubo::coordenadasDeCamera(Matriz mundoToCamera)
{
    this->centro = VerticeToPonto(mundoToCamera * PontoToVertice(this->centro));
    for (int i = 0; i < 8; i++)
    {
        vertices[i] = VerticeToPonto(mundoToCamera * PontoToVertice(this->vertices[i]));
    }

    atualizaFaces2();
}

//Utilizar Vertice
void Cubo::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    //this->centro = cameraToWorld * this->centro;
    //for (int i = 0; i < 8; i++)
    //{
    //    vertices[i] = cameraToWorld * vertices[i];
    //}
    //atualizaFaces();
}

void Cubo::setNormal(Ponto intersect)
{
    this->normal_intersect = intersect;
}

Ponto Cubo::rayIntersect(Ponto rayOrigin, Ponto rayDirection) {
    double distance = MAXFLOAT;
    Ponto closest_intersection = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    for (int i = 0; i < 12; i++) {
        Face face = this->faces[i];
        Ponto intersection = face.rayCasting(rayOrigin, rayDirection);
        double intersectionDistance = sqrt(pow(intersection[0] - rayOrigin[0], 2) + pow(intersection[1] - rayOrigin[1], 2) + pow(intersection[2] - rayOrigin[2], 2));
        if (intersection[2] < MAXFLOAT && intersectionDistance < distance)
        {
            distance = intersectionDistance;
            closest_intersection = intersection;
            setNormal(face.getNormal());
        }
    }
    return closest_intersection;
};

Ponto Cubo::normal(Ponto ponto)
{
    return this->normal_intersect;
}

//Ponto* Cubo::Bounds()
//{
//    Ponto minBounds = this->vertices[0];
//    Ponto maxBounds = this->vertices[0];
//    for (int i = 0; i < 8; i++)
//    {
//        if (vertices[i][0] > maxBounds[0])
//        {
//            maxBounds[0] = vertices[i][0];
//        }
//        if (vertices[i][1] > maxBounds[1])
//        {
//            maxBounds[1] = vertices[i][1];
//        }
//        if (vertices[i][2] > maxBounds[2])
//        {
//            maxBounds[2] = vertices[i][2];
//        }
//        if (vertices[i][0] < minBounds[0])
//        {
//            minBounds[0] = vertices[i][0];
//        }
//        if (vertices[i][1] < minBounds[1])
//        {
//            minBounds[1] = vertices[i][1];
//        }
//        if (vertices[i][2] < minBounds[2])
//        {
//            minBounds[2] = vertices[i][2];
//        }
//    }
//
//    return new Ponto(minBounds, maxBounds);
//}

// =========================== ROTAÇÃO =========================

// Returns a rotation matrix over the X eixo

Matriz Cubo::rotacaoX(float theta) {
    Matriz rot;
    rot << 1, 0, 0, 0,
        0, cos(theta), -sin(theta), 0,
        0, sin(theta), cos(theta), 0,
        0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over the Y eixo

Matriz  Cubo::rotacaoY(float theta) {
    Matriz rot;
    rot << cos(theta), 0, sin(theta), 0,
        0, 1, 0, 0,
        -sin(theta), 0, cos(theta), 0,
        0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over the Z eixo

Matriz  Cubo::rotacaoZ(float theta) {
    Matriz rot;
    rot << cos(theta), -sin(theta), 0, 0,
        sin(theta), cos(theta), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over an arbitrary eixo

Matriz  Cubo::rotacao(Ponto eixo, float theta) {
    Matriz rot;
    float c = cos(theta);
    float s = sin(theta);
    float t = 1 - c;
    float x = eixo(0);
    float y = eixo(1);
    float z = eixo(2);
    rot << t * x * x + c, t* x* y - s * z, t* x* z + s * y, 0,
        t* x* y + s * z, t* y* y + c, t* y* z - s * x, 0,
        t* x* z - s * y, t* y* z + s * x, t* z* z + c, 0,
        0, 0, 0, 1;
    return rot;
}