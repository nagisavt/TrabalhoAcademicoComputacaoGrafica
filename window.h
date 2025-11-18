#ifndef WINDOW_H
#define WINDOW_H

#include <QMatrix4x4>
#include <QVector3D>

class Window {
public:
    Window();

    //MANipular a Windows
    void pan(double dx, double dy);
    void zoom(double factor);

    void rotateX(double degrees);
    void rotateY(double degrees);
    void rotateZ(double degrees);

    QMatrix4x4 getViewMatrix() const;

    QVector3D getCentro() const { return centro; }

private:
    QVector3D centro;
    QVector3D rotacao;
    double altura;
};

#endif // WINDOW_H
