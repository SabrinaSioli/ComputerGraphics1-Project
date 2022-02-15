#pragma once
#include "Utils.h"
#include "Camera.h"

class Cenario
{
public:
    Camera camera;
    vector<Shape*> shapes;
    IluminacaoAmbiente luzAmbiente;
    vector<Iluminacao*> luzes;
    Ponto canvas[ALTURA][LARGURA];
    float* canvas_opengl;
    float frame[ALTURA * LARGURA * 3];
    Cenario();
    void addShape(Shape* shape);
    void addLight(Iluminacao* light);
    void setCamera(Camera camera);
    void setAmbientLight(IluminacaoAmbiente luzAmbiente);
    void colocarCoordenadasDeMundo();
    void coordenadasDeCamera();
    void rayCasting();
};