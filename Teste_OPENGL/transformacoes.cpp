#include "transformacoes.h"

// TRANSFORMAÇÕES

// ============================= ESCALONAMENTO ===============================

//Matrix4f escalonamento(float sx, float sy, float sz) {
//    Matrix4f mEscalonamento;
//    mEscalonamento << sx, 0, 0, 0,
//        0, sy, 0, 0,
//        0, 0, sz, 0,
//        0, 0, 0, 1;
//    return mEscalonamento;
//}

// ============================= TRANSLAÇÃO ================================

void translacao(Point t) {}

// ============================= ESPELHAMENTO ===============================

// PLANO YZ 

Matrix4f espelhamentoYZ() {
    Matrix4f mEspelhamento;
    mEspelhamento << -1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    return mEspelhamento;
}

// PLANO XZ

Matrix4f espelhamentoXZ() {
    Matrix4f mEspelhamento;
    mEspelhamento << 1, 0, 0, 0,
        0, -1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    return mEspelhamento;
}

// PLANO XY

Matrix4f espelhamentoXY() {
    Matrix4f mEspelhamento;
    mEspelhamento << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, -1, 0,
        0, 0, 0, 1;
    return mEspelhamento;
}


// PLANO ARBITRÁRIO

Matrix4f espelhamento(float a, float b, float c, float d)
{
    Matrix4f mEspelhamento;
    mEspelhamento << 1 - 2 * a * a, -2 * a * b, -2 * a * c, -2 * a * d,
        -2 * a * b, 1 - 2 * b * b, -2 * b * c, -2 * b * d,
        -2 * a * c, -2 * b * c, 1 - 2 * c * c, -2 * c * d,
        -2 * a * d, -2 * b * d, -2 * c * d, 1 - 2 * d * d;
    return mEspelhamento;
}

