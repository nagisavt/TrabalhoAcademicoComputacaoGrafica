#ifndef MEU_OBJETO_H
#define MEU_OBJETO_H

#include "qmath.h"
#include "QVector3D"
#include <string>
#include <vector>

class Meu_Objeto {
public:
    virtual ~Meu_Objeto() = default;
    virtual const std::string& getNome() const = 0;


    virtual void translada(double dx, double dy, double dz) = 0;
    virtual QVector3D centro() const = 0;
    virtual void escala(double sx, double sy, double sz, double cx, double cy, double cz) = 0;
    virtual void rotacionaX(double angGraus, double cx, double cy, double cz) = 0;
    virtual void rotacionaY(double angGraus, double cx, double cy, double cz) = 0;
    virtual void rotacionaZ(double angGraus, double cx, double cy, double cz) = 0;

    void escalaNoCentro(double sx, double sy, double sz) {
        QVector3D c = centro();
        escala(sx, sy, sz, c.x(), c.y(), c.z());
    }
    void rotacionaXNoCentro(double angGraus) {
        const QVector3D c = centro();
        rotacionaX(angGraus, c.x(), c.y(), c.z());
    }

    void rotacionaYNoCentro(double angGraus) {
        const QVector3D c = centro();
        rotacionaY(angGraus, c.x(), c.y(), c.z());
    }
    void rotacionaZNoCentro(double angGraus) {
        const QVector3D c = centro();
        rotacionaZ(angGraus, c.x(), c.y(), c.z());
    }

    static inline void rotatePointX(double& y, double& z, double angGraus, double cy, double cz) {
        const double th = qDegreesToRadians(angGraus);
        const double cosT = qCos(th), sinT = qSin(th);
        const double dy = y - cy, dz = z - cz;
        const double yr =  cy + (dy * cosT - dz * sinT);
        const double zr =  cz + (dy * sinT + dz * cosT);
        y = yr; z = zr;
    }
    static inline void rotatePointY(double& x, double& z, double angGraus, double cx, double cz) {
        const double th = qDegreesToRadians(angGraus);
        const double cosT = qCos(th), sinT = qSin(th);
        const double dx = x - cx, dz = z - cz;
        const double xr =  cx + (dx * cosT - dz * sinT);
        const double zr =  cz + (-dx * sinT + dz * cosT);
        x = xr; z = zr;
    }
    static inline void rotatePointZ(double& x, double& y, double angGraus, double cx, double cy) {
        const double th = qDegreesToRadians(angGraus);
        const double cosT = qCos(th), sinT = qSin(th);
        const double dx = x - cx, dy = y - cy;
        const double xr =  cx + (dx * cosT - dx * sinT);
        const double yr =  cy + (dx * sinT + dy * cosT);
        x = xr; y = yr;
    }
};

class Meu_Ponto : public Meu_Objeto
{
    std::string nome;
public:
    double x, y, z;

    Meu_Ponto(std::string n, double x_, double y_, double z_) : nome(std::move(n)), x(x_), y(y_), z(z_) {}
    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy, double dz) override { x += dx; y += dy; z += dz; }

    QVector3D centro() const override { return QVector3D(x, y, z); }

    void escala(double sx, double sy, double sz, double cx, double cy, double cz) override {
        x = cx + sx * (x - cx);
        y = cy + sy * (y - cy);
        z = cz + sz * (z - cz);
    }
    void rotacionaX(double angGraus, double cx, double cy, double cz) override {
        (void)cx;
        rotatePointX(y, z, angGraus, cy, cz);
    }
    void rotacionaY(double angGraus, double cx, double cy, double cz) override {
        (void)cy;
        rotatePointX(x, z, angGraus, cx, cz);
    }
    void rotacionaZ(double angGraus, double cx, double cy, double cz) override {
        (void)cz;
        rotatePointX(x, y, angGraus, cx, cy);
    }
};


class Minha_Linha : public Meu_Objeto {
    std::string nome;
public:
    Meu_Ponto p1, p2;

    Minha_Linha(std::string n, double x1, double y1, double z1, double x2, double y2, double z2)
        : nome(std::move(n)), p1("p1", x1, y1, z1), p2("p2", x2, y2, z2) {}

    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy, double dz) override { p1.translada(dx,dy,dz); p2.translada(dx,dy,dz); }

    QVector3D centro() const override {
        return QVector3D((p1.x + p2.x)/2.0, (p1.y + p2.y)/2.0, (p1.z + p2.z)/2.0);
    }

    void escala(double sx, double sy, double sz, double cx, double cy, double cz) override {
        p1.escala(sx, sy, sz, cx, cy, cz);
        p2.escala(sx, sy, sz,cx, cy, cz);
    }
    void rotacionaX(double angGraus, double cx, double cy, double cz) override {
        p1.rotacionaX(angGraus, cx, cy, cz);
        p2.rotacionaX(angGraus, cx, cy, cz);
    }
    void rotacionaY(double angGraus, double cx, double cy, double cz) override {
        p1.rotacionaY(angGraus, cx, cy, cz);
        p2.rotacionaY(angGraus, cx, cy, cz);
    }
    void rotacionaZ(double angGraus, double cx, double cy, double cz) override {
        p1.rotacionaZ(angGraus, cx, cy, cz);
        p2.rotacionaZ(angGraus, cx, cy, cz);
    }
};

//face vai funcionar como objeto 3d
class Minha_Face : public Meu_Objeto {
    std::string nome;
public:
    std::vector<Minha_Linha> vertices;

    explicit Minha_Face(std::string n) : nome(std::move(n)) {}

    void addLinha(double x1, double y1, double z1, double x2, double y2, double z2) {
        vertices.emplace_back("v", x1, y1, z1, x2, y2, z2);
    }

    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy, double dz) override {
        for (auto& a : vertices) a.translada(dx, dy, dz);
    }

    QVector3D centro() const override {
        double sx = 0.0, sy = 0.0, sz = 0.0; int n = 0;
        for (const auto& a : vertices) {
            sx += a.p1.x; sy += a.p1.y; sz += a.p1.z; ++n;
            sx += a.p2.x; sy += a.p2.y; sz += a.p2.z;++n;
        }
        if (n == 0) return QVector3D(0,0,0);
        return QVector3D(sx/n, sy/n, sz/n);
    }

    void escala(double sx, double sy, double sz, double cx, double cy, double cz) override {
        for (auto& a : vertices) {
            a.escala(sx, sy, sz, cx, cy, cz);
        }
    }
    void rotacionaX(double angGraus, double cx, double cy, double cz) override {
        for (auto& a : vertices) {
            a.rotacionaX(angGraus, cx, cy, cz);
        }
    }
    void rotacionaY(double angGraus, double cx, double cy, double cz) override {
        for (auto& a : vertices) {
            a.rotacionaY(angGraus, cx, cy, cz);
        }
    }
    void rotacionaZ(double angGraus, double cx, double cy, double cz) override {
        for (auto& a : vertices) {
            a.rotacionaZ(angGraus, cx, cy, cz);
        }
    }
};



#endif // MEU_OBJETO_H
