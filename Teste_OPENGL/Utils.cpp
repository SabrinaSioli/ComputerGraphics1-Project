#include "Utils.h"

Vertice PontoToVertice(Ponto p) {
    Vertice r(p[0], p[1], p[2], 1);
    return r;
}

Ponto VerticeToPonto(Vertice p) {
    Ponto r(p[0], p[1], p[2]);
    return r;
}

Material::Material() {};
Material::Material(Ponto ka, Ponto kd, Ponto ks, float shininess)
{
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;
};

Face::Face() {
    v1 = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v2 = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v3 = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
};

Face::Face(Ponto Vertice1, Ponto Vertice2, Ponto Vertice3) {
    this->v1 = Vertice1;
    this->v2 = Vertice2;
    this->v3 = Vertice3;
    this->v1v2 = this->v2 - this->v1;
    this->v1v3 = this->v3 - this->v1;
    this->v2v3 = this->v3 - this->v2;
    this->v3v1 = this->v1 - this->v3;

    this->normal = (v1v2.cross(v1v3)).normalized();
}

Ponto Face::intersecaoNoPlano(Ponto rayOrigin, Ponto rayDirection)
{
    float t;
    Ponto v_aux1 = this->v1 - rayOrigin;
    float prod = this->normal.dot(rayDirection);

    if (prod == 0)
    {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }

    else
    {
        t = (this->normal.dot(v_aux1)) / prod;
    }
    Ponto intersecaoNoPlano = rayOrigin + (rayDirection * t);
    return intersecaoNoPlano;
};

Ponto Face::rayCasting(Ponto rayOrigin, Ponto rayDirection)
{
    Ponto intersecaoNoPlano = this->intersecaoNoPlano(rayOrigin, rayDirection);

    if (intersecaoNoPlano[2] == MAXFLOAT)
    {
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }


    Ponto p1p2 = this->v2 - this->v1;
    Ponto p1p3 = this->v3 - this->v1;
    Ponto p2p3 = this->v3 - this->v2;
    Ponto p3p1 = this->v1 - this->v3;

    Ponto n = (p1p2.cross(p1p3)).normalized();

    Ponto p1pi = intersecaoNoPlano - this->v1;
    Ponto p2pi = intersecaoNoPlano - this->v2;
    Ponto p3pi = intersecaoNoPlano - this->v3;


    if (p1p2.cross(p1pi).dot(p1p2.cross(p1p3)) < 0)
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if (p2p3.cross(p2pi).dot(p1p2.cross(p1p3)) < 0)
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if (p3p1.cross(p3pi).dot(p1p2.cross(p1p3)) < 0)
        return Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);


    return intersecaoNoPlano;
}

void Face::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice a = PontoToVertice(this->v1v2);
    Vertice b = PontoToVertice(this->v1v3);
    Vertice c = PontoToVertice(this->v2v3);
    Vertice d = PontoToVertice(this->v3v1);

    a = mundoToCamera * a;
    b = mundoToCamera * b;
    c = mundoToCamera * c;
    d = mundoToCamera * d;

    v1v2 = VerticeToPonto(a);
    v1v3 = VerticeToPonto(b);
    v2v3 = VerticeToPonto(c);
    v3v1 = VerticeToPonto(d);

    this->normal = v1v2.cross(v1v3).normalized();
}

Ponto Face::getNormal()
{
    return this->normal;
};

// ============================== ILUMINAÇÃO =============================


Iluminacao::Iluminacao() {};
//float Iluminacao::fatorDifuso(Ponto ponto,  Ponto normal) { return 0.0; };
//float Iluminacao::fatorEspecular(Ponto ponto,  Ponto normal) { return 0.0; };
//Ponto Iluminacao::difuseIntensity(Ponto ponto,  Ponto normal, Material mat) { return Ponto(0.0, 0.0, 0.0); };
//Ponto Iluminacao::specularIntensity(Ponto ponto,  Ponto normal, Material mat) { return Ponto(0.0, 0.0, 0.0); };
//void Iluminacao::coordenadasDeCamera(Matriz mundoToCamera) {};
//void Iluminacao::colocarCoordenadasDeMundo(Matriz cameraToWorld) {};


IluminacaoAmbiente::IluminacaoAmbiente() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
};

IluminacaoAmbiente::IluminacaoAmbiente(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
};

Ponto IluminacaoAmbiente::ambientIntensity(Ponto ponto,  Material mat)
{
    Ponto intensity;
    intensity[0] = this->r * mat.ka[0];
    intensity[1] = this->g * mat.ka[1];
    intensity[2] = this->b * mat.ka[2];
    return intensity;
};

SpotIluminacao::SpotIluminacao(float r, float g, float b, Ponto posicao, Ponto direcao, float angulo)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->posicao = posicao;
    this->direcao = direcao.normalized();
    this->angulo = angulo;
};

/*double check*/
float SpotIluminacao::fatorDifuso(Ponto intersecao,  Ponto normal)
{
    Ponto lightDirection = this->posicao - intersecao;
    lightDirection = lightDirection.normalized();
    double ag = this->direcao.dot(-lightDirection);
    if (ag > cos(this->angulo))
    {
        return 0;
    }
    else
    {
        double fatorDifuso = lightDirection.dot(normal);
        if (fatorDifuso < 0)
        {
            return 0;
        }
        else
        {
            return fatorDifuso;
        }
    }
};

/*double check*/
float SpotIluminacao::fatorEspecular(Ponto ponto,  Ponto normal)
{
    Ponto lightDirection = (this->posicao - ponto).normalized();
    Ponto reflectedDirection = 2 * normal * (normal.dot(lightDirection)) - lightDirection;
    Ponto v = Ponto(0, 0, 0) - ponto;

    if ((-lightDirection).dot(this->direcao) > cos(this->angulo))
    {
        return 0;

    }
    else
    {
        float fatorEspecular = reflectedDirection.dot(v);
        if (fatorEspecular < 0)
        {
            return 0;
        }
        else
        {
            return fatorEspecular;
        }
    }
};

Ponto SpotIluminacao::difuseIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto difuse_intensity;
    difuse_intensity[0] = this->r * mat.kd[0];
    difuse_intensity[1] = this->g * mat.kd[1];
    difuse_intensity[2] = this->b * mat.kd[2];
    difuse_intensity = difuse_intensity * this->fatorDifuso(ponto, normal);
    return difuse_intensity;
};

Ponto SpotIluminacao::specularIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto specular_intensity;
    specular_intensity[0] = this->r * mat.ks[0];
    specular_intensity[1] = this->g * mat.ks[1];
    specular_intensity[2] = this->b * mat.ks[2];
    specular_intensity = specular_intensity * pow(this->fatorEspecular(ponto, normal), mat.shininess);
    return specular_intensity;
};

//Utilizar Vertice
void SpotIluminacao::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice p = Vertice(this->posicao[0], this->posicao[1], this->posicao[2], 1);
    Vertice d = Vertice(this->direcao[0], this->direcao[1], this->direcao[2], 1);
    p = mundoToCamera * p;
    d = mundoToCamera * d;

    this->posicao = Ponto(p[0], p[1], p[2]);
    this->direcao = Ponto(d[0], d[1], d[2]);
};

//Utilizar Vertice
void SpotIluminacao::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice p = Vertice(this->posicao[0], this->posicao[1], this->posicao[2], 1);
    Vertice d = Vertice(this->direcao[0], this->direcao[1], this->direcao[2], 1);
    p = cameraToWorld * p;
    d = cameraToWorld * d;

    this->posicao = Ponto(p[0], p[1], p[2]);
    this->direcao = Ponto(d[0], d[1], d[2]);
};

FarIluminacao::FarIluminacao(float r, float g, float b, Ponto direcao)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->direcao = direcao.normalized();
};

/*double check*/
float FarIluminacao::fatorDifuso(Ponto ponto,  Ponto normal)
{
    float fatorDifuso = (this->direcao * -1).dot(normal);
    if (fatorDifuso >= 0)
    {
        return fatorDifuso;
    }
    else
    {
        return 0;
    }
};

/*double check*/
float FarIluminacao::fatorEspecular(Ponto ponto,  Ponto normal)
{

    Ponto r = (2 * ((this->direcao * -1).dot(normal)) * normal) + this->direcao;
    Ponto v = Ponto(0, 0, 0) - ponto;
    float fatorEspecular = v.normalized().dot(r.normalized());

    if (fatorEspecular >= 0)
    {
        return fatorEspecular;
    }
    else
    {
        return 0;
    }

};

Ponto FarIluminacao::difuseIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];
    difuseIntensity = difuseIntensity * this->fatorDifuso(ponto, normal);
    return difuseIntensity;
};

Ponto FarIluminacao::specularIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * this->fatorEspecular(ponto, normal);
    return specularIntensity;
};
//Utilizar Vertice
void FarIluminacao::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice d = Vertice(this->direcao[0], this->direcao[1], this->direcao[2], 1);
    d = mundoToCamera * d;
    this->direcao = Ponto(d[0], d[1], d[2]);
};
//Utilizar Vertice
void FarIluminacao::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice d = Vertice(this->direcao[0], this->direcao[1], this->direcao[2], 1);
    d = cameraToWorld * d;
    this->direcao = Ponto(d[0], d[1], d[2]);
};

PontoLighting::PontoLighting(float r, float g, float b, Ponto posicao)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->posicao = posicao;
};

/*double check*/
float PontoLighting::fatorDifuso(Ponto ponto,  Ponto normal)
{   
    Ponto lightDirection = (this->posicao - ponto).normalized();
    float fatorDifuso = lightDirection.dot(normal.normalized());

    if (fatorDifuso >= 0)
    {
        return fatorDifuso;
    }
    else
    {
        return 0;
    }
};

/*double check*/
float PontoLighting::fatorEspecular(Ponto intersecao,  Ponto normal)
{   

    Ponto p = this->posicao - intersecao;
    Ponto l = p.normalized();

    Ponto r = (2 * ((l).dot(normal)) * normal) - l;
    Ponto v = Ponto(0, 0, 0) - intersecao;

    float fatorEspecular = v.normalized().dot(r.normalized());

    if (fatorEspecular >= 0)
    {
        return fatorEspecular;
    }
    else
    {
        return 0;
    }
};

/*need to implement materials*/
Ponto PontoLighting::difuseIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];

    difuseIntensity = difuseIntensity * this->fatorDifuso(ponto, normal);
    return difuseIntensity;
};

Ponto PontoLighting::specularIntensity(Ponto ponto,  Ponto normal, Material mat)
{
    Ponto specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * pow(this->fatorEspecular(ponto, normal), mat.shininess);
    return specularIntensity;
};

//Utilizar Vertice
void PontoLighting::coordenadasDeCamera(Matriz mundoToCamera)
{
    Vertice d = Vertice(this->posicao[0], this->posicao[1], this->posicao[2], 1);
    d = mundoToCamera * d;
    this->posicao = Ponto(d[0], d[1], d[2]);
};

//Utilizar Vertice
void PontoLighting::colocarCoordenadasDeMundo(Matriz cameraToWorld)
{
    Vertice d = Vertice(this->posicao[0], this->posicao[1], this->posicao[2], 1);
    d = cameraToWorld * d;
    this->posicao = Ponto(d[0], d[1], d[2]);
}