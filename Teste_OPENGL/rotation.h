#pragma once
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
using namespace std;

Matrix4f rotateX(float theta);
Matrix4f rotateY(float theta);
Matrix4f rotateZ(float theta);
Matrix4f rotate(Vector3f axis, float theta);