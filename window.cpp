#include "window.h"
#include "Mat.h"
#include <qdebug.h>

Window::Window() {
    camX = 25.0;
    camY = 40.0;
    camZ = 1000.0;
    angX = 0.0; angY = 0.0; angZ = 0.0;
    largura = 1000.0;
    altura = 1000.0;
}

void Window::pan(double dx, double dy, double dz) {
    camX += dx;
    camY += dy;
    camZ += dz;
}

void Window::zoom(double factor) {
    altura *= factor;
    largura *= factor;
}

void Window::rotateX(double degrees) { angX += degrees; }

void Window::rotateY(double degrees) { angY += degrees; }

void Window::rotateZ(double degrees) { angZ += degrees; }

Matriz4x4 Window::getViewMatriz() const {
    Matriz4x4 T = matrizTranslacao(-camX, -camY, -camZ);

    Matriz4x4 Ry = rotacaoY(-angY);
    Matriz4x4 Rx = rotacaoX(-angX);
    Matriz4x4 Rz = rotacaoZ(-angZ);
    Matriz4x4 R = multplicarMatrizes(Rz, multplicarMatrizes(Rx, Ry));

    Matriz4x4 S = identidade();
    if (largura > 0 && altura > 0) {
        S.m[0][0] = 2.0 / largura;
        S.m[1][1] = 2.0 / altura;
        S.m[2][2] = 2.0 / ( (largura+altura)/2.0 );
    }

    Matriz4x4 RT = multplicarMatrizes(R, T);
    return multplicarMatrizes(S, RT);
}
