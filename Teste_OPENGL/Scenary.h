#pragma once
#include "axx.h"
#include "Camera.h"
#include "Lighting.h"

class Scenary
{
public:
    Camera camera;
    vector<Shape*> shapes;
    AmbientLighting ambientLight;
    vector<Lighting*> lights;
    Point canvas[HEIGHT][WIDTH];
    float* canvas_opengl;
    float frame[HEIGHT * WIDTH * 3];
    Scenary();
    void addShape(Shape* shape);
    void addLight(Lighting* light);
    void setCamera(Camera camera);
    void setAmbientLight(AmbientLighting ambientLight);
    void setWorldCoordinates();
    void setCameraCoordinates();
    void rayCasting();
};