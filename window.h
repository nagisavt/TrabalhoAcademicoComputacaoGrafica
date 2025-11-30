#ifndef WINDOW_H
#define WINDOW_H

#include <QPointF>
#include "Mat.h"

class Window {
public:
    Window();

    void pan(double dx, double dy, double dz);
    void zoom(double factor);

    void rotateX(double degrees);
    void rotateY(double degrees);
    void rotateZ(double degrees);

    void ajustarAspectRatio(double ratio);

    Matriz4x4 getViewMatriz() const;

private:

    double camX, camY, camZ;

    double angX, angY, angZ;

    double largura;
    double altura;
};

#endif // WINDOW_H
