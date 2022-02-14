#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
using namespace std;

Matrix4f shearingXZtoX(float gamma);
Matrix4f sheringXZtoY(float gamma);
Matrix4f shearingXZtoZ(float gamma);
Matrix4f shearing(float gamma);