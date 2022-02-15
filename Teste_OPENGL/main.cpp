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
    // Pessego -----------------------------------------------
    Ponto La1 = { 0.831, 0.454, 0.337 };       //ambiente
    Ponto Ld1 = { 0.831, 0.454, 0.337 };       //difuso
    Ponto Ls1 = { 0.931, 0.554, 0.337 };       //
    double met1 = 0;
    auto* material1 = new Material(La1, Ld1, Ls1, met1);

    // Cinza roda ----------------------------------------
    Ponto La2 = { 0.458, 0.450, 0.549 };
    Ponto Ld2 = { 0.458, 0.450, 0.549 };
    Ponto Ls2 = { 0.458, 0.450, 0.549 };
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

    // Azul meio claro ---------------------------------------
    Ponto ka6 = { 0.015, 0.486, 0.674 };
    Ponto kd6 = { 0.015, 0.486, 0.674 };
    Ponto ks6 = { 0.015, 0.486, 0.674 };
    double m6 = 76;
    auto* material6 = new Material(ka6, kd6, ks6, m6);

    // Imbuia ------------------------------------------------
    Ponto La7 = { 0.501, 0.329, 0.172 };
    Ponto Ld7 = { 0.501, 0.329, 0.172 };
    Ponto Ls7 = { 0.501, 0.329, 0.172 };
    double met7 = 76;
    auto* material7 = new Material(La7, Ld7, Ls7, met7);

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

    // Meio amarelo ------------------------------------------
    Ponto La10 = { 0.839, 0.764, 0.262 };
    Ponto Ld10 = { 0.839, 0.764, 0.262 };
    Ponto Ls10 = { 0.839, 0.764, 0.262 };
    double met10 = 50;
    auto* material10 = new Material(La10, Ld10, Ls10, met10);

    // Vermelho cilindro -------------------------------------------------
    Ponto La11 = { 0.921, 0.298, 0.298 };
    Ponto Ld11 = { 0.921, 0.298, 0.298 };
    Ponto Ls11 = { 0.921, 0.298, 0.298 };
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

    // Laranja sol --------------------------------------------
    //0.925, 0.733, 0.105
    Ponto La18 = { 0.925, 0.733, 0.105 };
    Ponto Ld18 = { 0.925, 0.733, 0.105 };
    Ponto Ls18 = { 0.925, 0.733, 0.105 };
    double met18 = 50;
    auto* material18 = new Material(La18, Ld18, Ls18, met18);

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
    //(float raio, float altura, Ponto centro_base, Ponto eixo, Material mat)

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

    // -------------------------------- Cama ------------------------------------------------------------
    /*Cilindro CamaPe1(0.5, 2, Ponto(-18, -19, -68), Ponto(0, 1, 0), *material3); //tras
    Cilindro CamaPe2(0.5, 2, Ponto(-18, -19, -45), Ponto(0, 1, 0), *material3); //frente
    Cilindro CamaPe3(0.5, 2, Ponto(-4, -19, -68), Ponto(0, 1, 0), *material3);  //tras
    Cilindro CamaPe4(0.5, 2, Ponto(-4, -19, -45), Ponto(0, 1, 0), *material3);  //frente 

    Cubo CamaP1(14, { -11, -16, -56.5 }, *material4);
    Cubo CamaP2(14, { -11, -14, -56.5 }, *material5);

    CamaP1.escalonamento(Ponto(1.25, 0.15, 1.80));
    CamaP2.escalonamento(Ponto(1.25, 0.15, 1.80));

    Cubo Travesseiro(3, { -9.5, -13, -65 }, *material6);
    Travesseiro.escalonamento(Ponto(2.5, 1, 2));

    // -------------------------------- Mesa ------------------------------------------------------------
    Cubo MesaPe1(4, { 16, -15, -68 }, *material7); //1
    Cubo MesaPe2(4, { 6, -15, -68 }, *material7);  //2
    Cubo MesaPe3(4, { 16, -15, -60 }, *material7); //3
    Cubo MesaPe4(4, { 6, -15, -60 }, *material7);  //4 

    MesaPe1.escalonamento(Ponto(0.2, 2.0, 0.2));
    MesaPe2.escalonamento(Ponto(0.2, 2.0, 0.2));
    MesaPe3.escalonamento(Ponto(0.2, 2.0, 0.2));
    MesaPe4.escalonamento(Ponto(0.2, 2.0, 0.2));

    Cubo MesaCima(12, { 11, -11, -64 }, *material8);

    MesaCima.escalonamento(Ponto(1.0, 0.2, 0.85));

    //------------------------------ Cadeira ------------------------------------------------------------
    Cubo CadeiraPe1(2, { 9, -15, -58 }, *material7);
    Cubo CadeiraPe2(2, { 13, -15, -58 }, *material7);
    Cubo CadeiraPe3(2, { 9, -15, -54 }, *material7);
    Cubo CadeiraPe4(2, { 13, -15, -54 }, *material7);

    Cubo Cadeira(9, { 11, -13, -56 }, *material9);

    CadeiraPe1.escalonamento(Ponto(0.2, 2.0, 0.2));
    CadeiraPe2.escalonamento(Ponto(0.2, 2.0, 0.2));
    CadeiraPe3.escalonamento(Ponto(0.2, 2.0, 0.2));
    CadeiraPe4.escalonamento(Ponto(0.2, 2.0, 0.2));

    Cadeira.escalonamento(Ponto(0.5, -0.1, 0.5));

    // -------------------------------- Abajur ----------------------------------------------------------
    Cone AbCorpo(1, 3, Ponto(14, -10, -65), Ponto(0, 1, 0), *material9);
    AbCorpo.escalonamento(Ponto(1.0, 2.0, 1.0));

    Cilindro AbCabeca(2, 3, Ponto(14, -6, -65), Ponto(0, 1, 0), *material10);
    AbCabeca.escalonamento(Ponto(1.0, 0.8, 1.0));

    // -------------------------------- Planta ----------------------------------------------------------
    Esfera PlantaC(2.5, { -16, -15, -35 }, *material13);

    Cone Jarro(2, 3, { -16, -18, -35 }, { 0, -1, 0 }, *material11);
    Cilindro Tronco(0.5, 2, Ponto(-16, -18, -35), Ponto(0, 1, 0), *material12);

    // Quadro: ABAPURU ----------------------------------------------------------------------------------
    //-20, -6, -50 : PAREDE
    Cubo Moldura1(2, { -19, -3, -40 }, *material14);
    Cubo Moldura2(2, { 0, 0, 0 }, *material14);
    Cubo Moldura3(2, { -19, -3, -51 }, *material14);
    Cubo Moldura4(2, { 0, 0, 0 }, *material14);

    Moldura1.escalonamento(Ponto(0.1, 5.0, 0.25));
    Moldura2.escalonamento(Ponto(0.1, 5.2, 0.25));
    Moldura3.escalonamento(Ponto(0.1, 5.0, 0.25));
    Moldura4.escalonamento(Ponto(0.1, 5.2, 0.25));
    //-19, 1.68, -45.5
    Moldura2.Rotate(PI / 2, { 1, 0, 0 });
    Moldura2.Translating(Ponto(-19, 1.68, -45.5));
    //-19, -7.68, -45.5
    Moldura4.Rotate(PI / 2, { 1, 0, 0 });
    Moldura4.Translating(Ponto(-19, -7.68, -45.5));

    Cubo Quadro(2, { -19, -3, -45.5 }, *material15);
    Quadro.escalonamento(Ponto(0.1, 4.4, 5.2));

    Cubo QChao(2, { -18.9998, -6.4, -45.5 }, *material16);
    QChao.escalonamento(Ponto(0.1, 1, 5.2));

    Cubo Cacto1(1, { -18.9998, -3.5, -48.5 }, *material17);
    Cubo Cacto2(1, { -18.9998, -2, -49.5 }, *material17);
    Cubo Cacto3(1, { -18.9998, -3.3, -49 }, *material17);
    Cacto1.escalonamento(Ponto(0.2, 3.7, 0.8));
    Cacto2.escalonamento(Ponto(0.2, 3.7, 0.8));
    Cacto3.escalonamento(Ponto(0.2, 1.0, 0.8));

    Cubo Abaporu(2, { -18.9998, -3.2, -42 }, *material19);
    Abaporu.escalonamento(Ponto(0.2, 2.2, 1.4));

    Cubo Sol(2, { -18.9998, -1, -45.5 }, *material10);
    Cubo Sl1(1, { -18.998, -1, -45.5 }, *material18);
    Sol.escalonamento(Ponto(0.1, 1.0, 1.0));
    Sl1.escalonamento(Ponto(0.2, 0.8, 0.8));*/

    // ==================================================================================================
    //                     R    G    B
    IluminacaoAmbiente luzA(0.9, 0.9, 0.9);
    PontoLighting luzP(0.6, 0.6, 0.6, { 0, 20, -50 });
    //0, -20, -50 : CHAO


    //Posição, p/ onde a cam. esta olhando, UP vector
    /*Camera cam1({0, 10, 20}, {10, 0, -10}, {0, 11, -10}, -4, 5);
    Camera cam2({ -10, 0, 0 }, { 0, -20, -50 }, { -10, 1, 0 }, -4, 6);
    Camera cam3({ 35, 10, -20 }, { 0, -20, -50 }, { 35, 11, -20 }, -4, 5);
    Camera cam4({ 0, 50, -40 }, { 0, -20, -50 }, { 0, 51, -40 }, -4, 4);
    Camera camAux({ -11, 0, -56.5 }, { 14, -15, -65 }, { -11, 1, -56.5 }, -4, 4);
    Camera camPaint({ 60, 0, -50 }, { -19, -3, -45.5 }, { 60, 1, -50 }, -8, 2);*/

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


    /*cenario->addShape(&CamaPe1);
    cenario->addShape(&CamaPe2);
    cenario->addShape(&CamaPe3);
    cenario->addShape(&CamaPe4);
    cenario->addShape(&CamaP1);
    cenario->addShape(&CamaP2);
    cenario->addShape(&Travesseiro);

    cenario->addShape(&MesaPe1);
    cenario->addShape(&MesaPe2);
    cenario->addShape(&MesaPe3);
    cenario->addShape(&MesaPe4);
    cenario->addShape(&MesaCima);

    cenario->addShape(&CadeiraPe1);
    cenario->addShape(&CadeiraPe2);
    cenario->addShape(&CadeiraPe3);
    cenario->addShape(&CadeiraPe4);
    cenario->addShape(&Cadeira);

    cenario->addShape(&AbCorpo);
    cenario->addShape(&AbCabeca);

    cenario->addShape(&PlantaC);
    cenario->addShape(&Jarro);
    cenario->addShape(&Tronco);

    cenario->addShape(&Moldura1);
    cenario->addShape(&Moldura2);
    cenario->addShape(&Moldura3);
    cenario->addShape(&Moldura4);
    cenario->addShape(&Quadro);
    cenario->addShape(&QChao);
    cenario->addShape(&Cacto1);
    cenario->addShape(&Cacto2);
    cenario->addShape(&Cacto3);
    cenario->addShape(&Abaporu);
    cenario->addShape(&Sol);
    cenario->addShape(&Sl1);*/

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