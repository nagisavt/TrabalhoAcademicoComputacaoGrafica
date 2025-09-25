#ifndef WINDOW_H
#define WINDOW_H

#include <QTransform>
#include <QPointF>

class Window {
public:
    Window();

    //MANipular a Windows
    void pan(double dx, double dy);
    void zoom(double factor);
    void rotate(double degrees);

    QTransform getTransformacao() const;
    QPointF getCentro() const { return centro; }

private:
    QPointF centro;
    double altura;
    double angulo;
};

#endif // WINDOW_H
