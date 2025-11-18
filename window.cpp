#include "window.h"

Window::Window() {
    centro = QVector3D(50.0, 150.0, 0.0);
    rotacao = QVector3D(0.0, 0.0, 0.0);
    altura = 600.0;
}

void Window::pan(double dx, double dy) {
    centro.setX(centro.x() + dx);
    centro.setY(centro.y() + dy);
}

void Window::zoom(double factor) {
    altura *= factor;
}

void Window::rotateX(double degrees) {
    rotacao.setX(rotacao.x() + degrees);
}

void Window::rotateY(double degrees) {
    rotacao.setY(rotacao.y() + degrees);
}

void Window::rotateZ(double degrees) {
    rotacao.setZ(rotacao.z() + degrees);
}

QMatrix4x4 Window::getViewMatrix() const {
    QMatrix4x4 mat;
    double escala = 2.0 / altura;
    mat.scale(escala, -escala, escala);
    mat.rotate(rotacao.x(), 1, 0, 0);
    mat.rotate(rotacao.y(), 0, 1, 0);
    mat.rotate(rotacao.z(), 0, 0, 1);
    mat.translate(-centro.x(), -centro.y(), -centro.z());
    return mat;
}
