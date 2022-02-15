#include "Cenario.h"
#include <numeric>

Cenario::Cenario() {
    canvas_opengl = new float[ALTURA * LARGURA * 3];
};

void Cenario::addShape(Shape* shape)
{
    this->shapes.push_back(shape);
};

void Cenario::addLight(Iluminacao* light)
{
    this->luzes.push_back(light);
};

void Cenario::setCamera(Camera camera)
{
    this->camera = camera;
};

void Cenario::setAmbientLight(IluminacaoAmbiente luzAmbiente)
{
    this->luzAmbiente = luzAmbiente;
};

void Cenario::coordenadasDeCamera()
{
        
    for (int i = 0; i < this->shapes.size(); i++) {
        this->shapes[i]->coordenadasDeCamera(this->camera.mundoToCamera());
    }
    for (int i = 0; i < this->luzes.size(); i++) {
        this->luzes[i]->colocarCoordenadasDeMundo(this->camera.mundoToCamera());
    }

};

void Cenario::rayCasting()
{
    this->coordenadasDeCamera();
    Ponto intersect;

    double x, y, z;

    z = camera.d; // distancia

    double deslocamento = camera.plano_tamanho / ALTURA; //só faço uma vez visto que os lados têm o mesmo tamanho

    int idx = 0;

    Ponto rayOrigin = Ponto(0, 0, 0);
    for (int j = 0; j < ALTURA; j++)
    {
        y = -camera.plano_tamanho / 2 + deslocamento + j * deslocamento;
        for (int k = 0; k < LARGURA; k++)
        {
            x = -camera.plano_tamanho / 2 + deslocamento + k * deslocamento;

            Ponto nearest_point = Ponto(MAXFLOAT, MAXFLOAT, MAXFLOAT);

            Ponto rayDirection = Ponto(x, y, z);

            Shape* obj = nullptr;

            for (int i = 0; i < this->shapes.size(); i++)
            {
                intersect = this->shapes[i]->rayIntersect(rayOrigin, rayDirection);
                if (intersect.norm() < nearest_point.norm()) {
                    nearest_point = intersect;
                    obj = shapes[i];
                }
            }

            if (nearest_point[2] < MAXFLOAT) {
                Ponto intensity = this->luzAmbiente.ambientIntensity(nearest_point, obj->mat);

                for (int l = 0; l < this->luzes.size(); l++) {
                    intensity += this->luzes[l]->difuseIntensity(nearest_point, obj->normal(nearest_point), obj->mat);
                    intensity += this->luzes[l]->specularIntensity(nearest_point, obj->normal(nearest_point), obj->mat);
                }

                this->frame[idx * 3] = intensity[0];
                this->frame[idx * 3 + 1] = intensity[1];
                this->frame[idx * 3 + 2] = intensity[2];
            }
            else
            {
                frame[idx * 3] = luzAmbiente.r;
                frame[idx * 3 + 1] = luzAmbiente.g;
                frame[idx * 3 + 2] = luzAmbiente.b;
            }

            idx++;
        }
    }
};