#include <Windows.h>
#include <iostream>
#include "glut.h"

#include "Cone.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "Cubo.h"
#include "Cenario.h"

#pragma comment(lib, "glut32.lib")

using namespace std;

float x_start_posicao = 100;
float y_start_posicao = 100;

float H = 500;
float W = 500;

#define PI 3.1415

HWND hWnd;

float* tela;

void renderScene(void) {

    glDrawPixels(H, W, GL_RGB, GL_FLOAT, tela);
    glutSwapBuffers();
    glutPostRedisplay();
}

void Raycaster() {
    /* ================================== Materiais ========================================== */

    // Cinza roda ----------------------------------------
    Ponto La2 = { 0.254, 0.250, 0.309 };
    Ponto Ld2 = { 0.254, 0.250, 0.309 };
    Ponto Ls2 = { 0.254, 0.250, 0.309 };
    double met2 = 100;
    auto* material2 = new Material(La2, Ld2, Ls2, met2);

    // Preto magenta -----------------------------------------
    Ponto La3 = { 0.078, 0.078, 0.078 };
    Ponto Ld3 = { 0.078, 0.078, 0.078 };
    Ponto Ls3 = { 0.078, 0.078, 0.078 };
    double met3 = 100;
    auto* material3 = new Material(La3, Ld3, Ls3, met3);

    // Fosco -------------------------------------------------
    Ponto La4 = { 0.282, 0.282, 0.254 };
    Ponto Ld4 = { 0.282, 0.282, 0.254 };
    Ponto Ls4 = { 0.282, 0.282, 0.254 };
    double met4 = 12;
    auto* material4 = new Material(La4, Ld4, Ls4, met4);

    // Azul marinho -------------------------------------------
    Ponto La5 = { 0.141, 0.141, 0.549 };
    Ponto Ld5 = { 0.141, 0.141, 0.549 };
    //Ponto Ls5 = { 0, 0, 0 };
    Ponto Ls5 = { 0.141, 0.141, 0.549 };
    double met5 = 51;
    auto* material5 = new Material(La5, Ld5, Ls5, met5);

    // Imbuia mais claro -------------------------------------
    Ponto La8 = { 0.601, 0.429, 0.272 };
    Ponto Ld8 = { 0.601, 0.429, 0.272 };
    Ponto Ls8 = { 0.601, 0.429, 0.272 };
    double met8 = 76;
    auto* material8 = new Material(La8, Ld8, Ls8, met8);

    // Laranja -----------------------------------------------
    Ponto La9 = { 0.768, 0.286, 0.031 };
    Ponto Ld9 = { 0.968, 0.286, 0.031 };
    Ponto Ls9 = { 0.768, 0.286, 0.031 };
    double met9 = 50;
    auto* material9 = new Material(La9, Ld9, Ls9, met9);


    // Vermelho cilindro -------------------------------------------------
    Ponto La11 = { 1, 0.160, 0.196 };
    Ponto Ld11 = { 1, 0.160, 0.196 };
    Ponto Ls11 = { 1, 0.160, 0.196 };
    double met11 = 50;
    auto* material11 = new Material(La11, Ld11, Ls11, met11);

    // Madeira -----------------------------------------------
    Ponto La12 = { 0.262, 0.203, 0.192 };
    Ponto Ld12 = { 0.294, 0.078, 0.047 };
    Ponto Ls12 = { 0.294, 0.078, 0.047 };
    double met12 = 50;
    auto* material12 = new Material(La12, Ld12, Ls12, met12);

    // Verde -------------------------------------------------
    Ponto La13 = { 0.380, 0.466, 0.086 };
    Ponto Ld13 = { 0.294, 0.078, 0.047 };
    Ponto Ls13 = { 0.380, 0.466, 0.086 };
    double met13 = 50;
    auto* material13 = new Material(La13, Ld13, Ls13, met13);

    // Dourado -----------------------------------------------
    Ponto La14 = { 0.894, 0.737, 0.360 };
    Ponto Ld14 = { 0.894, 0.737, 0.360 };
    Ponto Ls14 = { 0.894, 0.737, 0.360 };
    double met14 = 1000;
    auto* material14 = new Material(La14, Ld14, Ls14, met14);

    // Azul da pintura ---------------------------------------
    Ponto La15 = { 0.392, 0.552, 0.741 };
    Ponto Ld15 = { 0.392, 0.552, 0.741 };
    Ponto Ls15 = { 0.392, 0.552, 0.741 };
    double met15 = 50;
    auto* material15 = new Material(La15, Ld15, Ls15, met15);

    // Verde1 da pintura --------------------------------------
    Ponto La16 = { 0.152, 0.360, 0.192 };
    Ponto Ld16 = { 0.152, 0.360, 0.192 };
    Ponto Ls16 = { 0.152, 0.360, 0.192 };
    double met16 = 50;
    auto* material16 = new Material(La16, Ld16, Ls16, met16);

    // Verde2 da pintura --------------------------------------
    Ponto La17 = { 0.341, 0.564, 0.349 };
    Ponto Ld17 = { 0.341, 0.564, 0.349 };
    Ponto Ls17 = { 0.341, 0.564, 0.349 };
    double met17 = 50;
    auto* material17 = new Material(La17, Ld17, Ls17, met17);

    // Branco rosado -------------------------------------------
    Ponto La19 = { 0.980, 0.925, 0.694 };
    Ponto Ld19 = { 0.980, 0.925, 0.694 };
    Ponto Ls19 = { 0.980, 0.925, 0.694 };
    double met19 = 50;
    auto* material19 = new Material(La19, Ld19, Ls19, met19);

    // Objetos do Cenario ===============================================================================
    // -------------------------------- Paredes e Chão --------------------------------------------------
    Cubo Parede1(40, { -20, 14, -10 }, * material3);
    Cubo Parede2(40, { 0, 14, -30 }, * material12);
    Cubo Chao(40, { 0, 0, -10 }, * material4);

    Camera cam1({ 0, 20, 40 }, { 0, 0, -10 }, { 0, 21, 40 }, -4, 8); // frente
    Camera cam2({ 45, 20, 10 }, { 0, 0, -10 }, { 45, 21, 10 }, -4, 8); //  direita
    Camera cam3({ 35, 10, -20 }, { 0, -20, -50 }, { 35, 11, -20 }, -4, 5); // esquerda
    Camera cam4({ 0, 50, -40 }, { 0, -20, -50 }, { 0, 51, -40 }, -4, 4); // cima
    Camera camAux({ -11, 0, -56.5 }, { 14, -15, -65 }, { -11, 1, -56.5 }, -4, 4);
    Camera camPaint({ 60, 0, -50 }, { -19, -3, -45.5 }, { 60, 1, -50 }, -8, 2);

    Cubo carroTras(15, { 5, 5, 0 }, * material17);
    Cubo carroCima(15, { 7.3, 9.5, 0 }, * material17);

    carroTras.escalonamento({ 1, 0.3, 0.5 });
    carroCima.escalonamento({ 0.7, 0.3, 0.5 });

    Esfera roda1(1.7, { 0, 3, -3.5 }, * material2);
    Esfera roda2(1.7, { 0, 3, 4.5 }, * material2);
    Esfera roda3(1.7, { 10, 3, -3.5 }, * material2);
    Esfera roda4(1.7, { 10, 3, 4.5 }, * material2);

    Cone cone2(1, 3, { 14, 2, 0 }, { 0, 1, 0 }, * material9);

    Cubo baseMesa(10, { 10, 6, -20 }, * material5);
    baseMesa.escalonamento({ 1, 0.2, 0.5 });
    Cilindro apoio1(1, 2, { 10, 2, -20 }, { 0, 1, 0 }, * material11);
    Cilindro apoio2(1, 2, { 5, 2, -20 }, { 0, 1, 0 }, * material11);


    // scalling -> alterar o tamanho dos objetos
    // translating -> mover o objeto
    // rotate -> rotacionar o objeto

    Parede1.escalonamento(Ponto(0.05, 0.7, 1.0));
    Parede2.escalonamento(Ponto(1.0, 0.7, 0.05));
    Chao.escalonamento(Ponto(1.0, 0.05, 1.0));

    // ==================================================================================================
    //                     R    G    B
    IluminacaoAmbiente luzA(0.9, 0.9, 0.9);
    PontoLighting luzP(0.6, 0.6, 0.6, { 0, 20, -50 });
    //0, -20, -50 : CHAO


    Cenario* cenario = new Cenario();

    cenario->setAmbientLight(luzA);
    cenario->addLight(&luzP);

    cenario->addShape(&Parede1);
    cenario->addShape(&Parede2);
    cenario->addShape(&Chao);

    cenario->addShape(&carroTras);
    cenario->addShape(&carroCima);

    cenario->addShape(&apoio1);
    cenario->addShape(&apoio2);

    cenario->addShape(&baseMesa);

    cenario->addShape(&cone2);



    cenario->addShape(&roda1);
    cenario->addShape(&roda2);
    cenario->addShape(&roda3);
    cenario->addShape(&roda4);

    cenario->setCamera(cam2);

    cenario->rayCasting();

    tela = cenario->frame;
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

    tela = new float[H * W * 3];

    Raycaster();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMainLoop();

    return 1;
}