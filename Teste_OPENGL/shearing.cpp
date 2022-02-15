#include "shearing.h";

//Returns a shearing matrix on the XZ plane in X direcao

Matrix4f shearingXZtoX(float gamma)
{
    Matrix4f shear;
    shear << 1, tan(gamma), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;

    return shear;
}

//Returns a shearing matrix on the XZ plane in Y direcao

Matrix4f sheringXZtoY(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
        tan(gamma), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;

    return shear;
}

//Returns a shearing matrix on the XZ plane in Z direcao

Matrix4f shearingXZtoZ(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, tan(gamma), 1, 0,
        0, 0, 0, 1;

    return shear;
}

Matrix4f shearing(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
        0, 1, tan(gamma), 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    
    return shear;
}