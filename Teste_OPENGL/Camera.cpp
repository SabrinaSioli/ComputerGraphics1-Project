#include "Camera.h"

//Camera::Camera(Ponto camera_pos, Ponto lookAt, Ponto viewUp, double gradeTam, double distGrade, int furos)
//: coordCamera(camera_pos), lookAt(lookAt), viewUp(viewUp), qtdFuros(furos) {
//	olho = Ponto(0, 0, 0);
//
//	kc = (camera_pos - lookAt).normalized();
//	ic = kc.cross(viewUp - coordCamera).normalized();
//	jc = ic.cross(kc);
//
//	double deslocamento = gradeTam / qtdFuros;
//	double x, y, z = distGrade;
//
//	// AQUI EU ALOCO ESPAÇO PRA TELA DE PIXELS
//
//	alocar_camera(gradeCamera, furos);
//
//	for (int j = 0; j < furos; ++j) {
//		x = gradeTam / 2 - deslocamento - j * deslocamento;
//		for (int k = 0; k < furos; ++k) {
//			y = -gradeTam / 2 + deslocamento + k * deslocamento;
//
//			gradeCamera[k][j] = Ponto(x, y, z);
//		}
//	}
//}

Camera::Camera() {};

Camera::Camera(Ponto eye, Ponto lookAt, Ponto viewUp, int d, int plano_tamanho) : d(d), plano_tamanho(plano_tamanho) {
    this->eye = eye;
    this->lookAt = lookAt;
    this->viewUp = viewUp;

    //this->k = (eye - lookAt).normalized();

    //this->i = (viewUp - eye).cross(k).normalized();

    //this->j = (k.cross(i)).normalized();

    this->k = (eye - lookAt).normalized();

    this->i = ((viewUp - eye).cross(k)).normalized();
    this->j = (k.cross(i)).normalized();
};

Matriz Camera::mundoToCamera()
{
    Matriz mundoToCamera;
    mundoToCamera << i[0], i[1], i[2], -i.dot(eye),
        j[0], j[1], j[2], -j.dot(eye),
        k[0], k[1], k[2], -k.dot(eye),
        0, 0, 0, 1;
    return mundoToCamera;
};

Matriz Camera::cameraToWorld() {
    Matriz cameraToWorld;
    cameraToWorld << i[0], j[0], k[0], eye[0],
        i[1], j[1], k[1], eye[1],
        i[2], j[2], k[2], eye[2],
        0, 0, 0, 1;
    return cameraToWorld;
};

void Camera::atualiza() {
    this->eye = eye;
    this->lookAt = lookAt;
    this->viewUp = viewUp;

    Ponto k = (eye - lookAt).normalized();

    Ponto i = (viewUp.cross(k)).normalized();
    Ponto j = (k.cross(i)).normalized();
};

void Camera::moverX(float x)
{
    this->eye.x() += x;
    atualiza();
};

void Camera::moverY(float y)
{
    this->eye.y() += y;
    atualiza();
};

void Camera::moverZ(float z)
{
    this->eye.z() += z;
    atualiza();
};

void Camera::moverPara(Ponto eye)
{
    this->eye = eye;
    atualiza();
};