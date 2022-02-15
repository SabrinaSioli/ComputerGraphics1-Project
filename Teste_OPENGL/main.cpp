#include <Windows.h>
#include <iostream>
#include "glut.h"

#include "Sphere.h"
#include "Cube.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Scenary.h"

#pragma comment(lib, "glut32.lib")

using namespace std;

float x_start_position = 100;
float y_start_position = 100;

float H = 500;
float W = 500;

#define PI 3.1415

HWND hWnd;

float* test;

void renderScene(void) {

    glDrawPixels(H, W, GL_RGB, GL_FLOAT, test);
    glutSwapBuffers();
    glutPostRedisplay();
}

void Raycaster() {
    Point ka1x = { 1, 1, 1 };
    Point kd1x = { 1, 1, 1 };
    Point ks1x = { 1, 1, 1 };
    double m1x = 1;

    auto* mat_1 = new Material(ka1x, kd1x, ks1x, m1x);


    Point ka1 = { 0.6, 0.2, 0 };
    Point kd1 = { 0.7038, 0.27048, 0.0828 };
    Point ks1 = { 0.256777, 0.137622, 0.086014 };
    double m1 = 12.8;
    auto* material1 = new Material(ka1, kd1, ks1, m1);

    //Polished copper
    Point ka2 = { 0.19125, 0.0735, 0.0225 };
    Point kd2 = { 0.7038, 0.27048, 0.0828 };
    Point ks2 = { 0.256777, 0.137622, 0.086014 };
    double m2 = 12.8;
    auto* material2 = new Material(ka2, kd2, ks2, m2);

    //Pearl
    Point ka3 = { 1, 0.4735, 0.5 };
    Point kd3 = { 1, 0.257048, 0.9 };
    Point ks3 = { 1, 0.2537622, 0.9 };
    double m3 = 11.264;
    auto* material3 = new Material(ka3, kd3, ks3, m3);


    //Fosco
    Point ka4 = { 0.2, 0.5, 0.9 };
    Point kd4 = { 0.1, 0.6, 0.9 };
    Point ks4 = { 0.1, 0.7, 0.774597 };
    double m4 = 5.8;
    auto* material4 = new Material(ka4, kd4, ks4, m4);

    //Bronze
    Point ka5 = { 0.24725, 0.1995, 0.0745 };
    Point kd5 = { 0.75164, 0.60648, 0.22648 };
    Point ks5 = { 0.628281, 0.555802, 0.366065 };
    double m5 = 51.2;
    auto* material5 = new Material(ka5, kd5, ks5, m5);

    //
    Point ka6 = { 0.4745, 0.01175, 0.01175 };
    Point kd6 = { 0.61424, 0.04136, 0.04136 };
    Point ks6 = { 0.727811, 0.626959, 0.626959 };
    double m6 = 76.8;
    auto* material6 = new Material(ka6, kd6, ks6, m6);

    //Verde
    Point ka7 = { 0.4745, 0.91175, 0.01175 };
    Point kd7 = { 0.61424, 0.04136, 0.04136 };
    Point ks7 = { 0.727811, 0.626959, 0.626959 };
    double m7 = 76.8;
    auto* material7 = new Material(ka7, kd7, ks7, m7);

    Point ka8 = { 0.5, 0.5, 0.5 };
    Point kd8 = { 0.1, 0.1, 0.1 };
    Point ks8 = { 0.774597, 0.774597, 0.774597 };
    double m8 = 12.8;
    auto* material8 = new Material(ka8, kd8, ks8, m8);

    Point ka9 = { 0.8, 0.8, 0.8 };
    Point kd9 = { 0.2, 0.2, 0.2 };
    Point ks9 = { 0.774597, 0.774597, 0.774597 };
    double m9 = 12.8;
    auto* material9 = new Material(ka9, kd9, ks9, m9);


    //Interação com a luz ambiente; '' com a luz difusa, '' com a luz (?), brilho

    // Objetos do Cenario ===============================================================================
    // // -------------------------------- Paredes e Chão --------------------------------------------------
    // -------------------------------- Paredes e Chão --------------------------------------------------
    Cube Parede1(40, { -20, -6, -50 }, *material4);
    Cube Parede2(40, { 0, -6, -70 }, *material4);
    Cube Chao(40, { 0, -20, -50 }, *material2);

    Parede1.Scalling(Point(0.05, 0.7, 1.0));
    Parede2.Scalling(Point(1.0, 0.7, 0.05));
    Chao.Scalling(Point(1.0, 0.05, 1.0));

    // -------------------------------- Cama ------------------------------------------------------------
    Cylinder CamaPe1(0.5, 2, Point(-18, -19, -68), Point(0, 1, 0), *material1);
    Cylinder CamaPe2(0.5, 2, Point(-18, -19, -55), Point(0, 1, 0), *material1);
    Cylinder CamaPe3(0.5, 2, Point(-12, -19, -68), Point(0, 1, 0), *material1);
    Cylinder CamaPe4(0.5, 2, Point(-12, -19, -55), Point(0, 1, 0), *material1);

    Cube CamaP1(14, { -15, -16, -61.5 }, *material4);
    Cube CamaP2(14, { -15, -14, -61.5 }, *material5);

    CamaP1.Scalling(Point(0.5, 0.15, 1.0));
    CamaP2.Scalling(Point(0.5, 0.15, 1.0));

    // -------------------------------- Mesa ------------------------------------------------------------
    Cube MesaPe1(4, { 16, -15, -68 }, *material1); //1
    Cube MesaPe2(4, { 6, -15, -68 }, *material1);//2
    Cube MesaPe3(4, { 16, -15, -60 }, *material1);//3
    Cube MesaPe4(4, { 6, -15, -60 }, *material1); //4 

    MesaPe1.Scalling(Point(0.2, 2.0, 0.2));
    MesaPe2.Scalling(Point(0.2, 2.0, 0.2));
    MesaPe3.Scalling(Point(0.2, 2.0, 0.2));
    MesaPe4.Scalling(Point(0.2, 2.0, 0.2));

    Cube MesaCima(12, { 11, -11, -64 }, *material1);

    MesaCima.Scalling(Point(1.0, 0.2, 0.85));

    // -------------------------------- Abajur ----------------------------------------------------------
    Cone AbCorpo(1, 3, 1, Point(14, -10, -65), Point(0, 1, 0), *material6);
    AbCorpo.scaling(Point(1.0, 2.0, 1.0));


    Cylinder AbCabeca(2, 3, Point(14, -6, -65), Point(0, 1, 0), *material1);
    AbCabeca.scaling(Point(1.0, 0.8, 1.0));



    // Montanha
    Cone Topo(12, 20, 1, Point(1, -15, -50), Point(0, 1, 0), *material9);
    Cone Base(20, 20, 1, Point(1, -20, -50), Point(0, 1, 0), *material8);


    //Arvore
    //float radius, Point center, Material mat);
    Sphere folha(10, { 16, -20, -68 }, *material3);
    Cylinder tronco(1, 15, Point(16, -20, -68), Point(0, 1, 0), *material1);




    // -------------------------------- Planta ----------------------------------------------------------


    Point a(45, 15, 0);
    Point b(14, -6, -65);
    Point c = (a + 40 * b.normalized());
    c[0] -= 25;
    c[2] += 25;
    //Sphere PlantaC(2, c, *material6);
    Sphere PlantaC(2, { 6, 5, -40 }, *material6);
    // ==================================================================================================

    AmbientLighting light(0.9, 0.9, 0.9);

    PointLighting plight(0.9, 0, 0, { 0, 0, 0 });

    //SpotLighting splight(1 / 255.f, 1 / 255.f, 1 / 255.f, { 0, 0, -15 }, { 0, 0, -20 }, 3.1415 / 2);

    FarLighting frlight(0.7, 0.7, 0.7, Point(0, 0, -1));

    //Posição, p/ onde a cam esta olhando, UP vector
    Camera cam({ 200, -10, 0 }, { 3, -6, -50 }, { 200, -9, -0 }, -4, 1.8);
    Scenary* cenario = new Scenary();

    //cenario->addLight(&plight);

    cenario->setAmbientLight(light);

    cenario->addShape(&Parede1);
    cenario->addShape(&Parede2);
    cenario->addShape(&Chao);

    /*
    cenario->addShape(&CamaPe1);
    cenario->addShape(&CamaPe2);
    cenario->addShape(&CamaPe3);
    cenario->addShape(&CamaPe4);
    cenario->addShape(&CamaP1);
    cenario->addShape(&CamaP2);
    */
    
    /*cenario->addShape(&MesaPe1);
    cenario->addShape(&MesaPe2);
    cenario->addShape(&MesaPe3);
    cenario->addShape(&MesaPe4);
    cenario->addShape(&MesaCima);

    cenario->addShape(&AbCorpo);
    cenario->addShape(&AbCabeca);
    */

    cenario->addShape(&Base);
    cenario->addShape(&Topo);

    cenario->addShape(&tronco);
    cenario->addShape(&folha);



    cenario->addShape(&PlantaC);

    cenario->setCamera(cam);

    cenario->rayCasting();

    test = cenario->frame;
}

int main(int argc, char** argv) {

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glClearColor(0, 0, 0, 0);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(H, W);
    glutCreateWindow("CUBO");

    glutPostRedisplay();

    test = new float[H * W * 3];

    Raycaster();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);


    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}