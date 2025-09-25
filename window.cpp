#include "window.h"

Window::Window() : centro(0.0, 0.0), altura(500.0), angulo(0.0) {

}

void Window::pan(double dx, double dy) {
    centro.setX(centro.x() + dx);
    centro.setY(centro.y() + dy);
}

void Window::zoom(double factor) {
    altura *= factor;
}

void Window::rotate(double degrees) {
    angulo += degrees;
}

QTransform Window::getTransformacao() const {
    QTransform t;
    t.translate(-centro.x(), -centro.y());
    t.rotate(-angulo);
    double escala = 2.0 / altura;
    t.scale(escala, escala);

    return t;
}
