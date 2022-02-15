
// Transformações
#pragma once
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
using namespace std;

typedef Eigen::Vector3f Point;
typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matriz;



//Matrix4f escalonamento(float sx, float sy, float sz);

void translacao(Point t);

Matrix4f espelhamentoYZ();
Matrix4f espelhamentoXZ();
Matrix4f espelhamentoXY();
Matrix4f espelhamento(float a, float b, float c, float d);
