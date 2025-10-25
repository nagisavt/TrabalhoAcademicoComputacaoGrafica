#include "window.h"

Window::Window() {
    centro = QPointF(50.0, 150.0);
    altura = 600.0;
    angulo = 0.0;
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
    double escala = 2.0 / altura;
    t.scale(escala, escala);
    t.rotate(-angulo);
    t.translate(-centro.x(), -centro.y());
    return t;
}
