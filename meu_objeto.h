#ifndef MEU_OBJETO_H
#define MEU_OBJETO_H


#include "qmath.h"
#include "qpoint.h"
#include <string>
#include <vector>

class Meu_Objeto {
public:
    virtual ~Meu_Objeto() = default;
    virtual const std::string& getNome() const = 0;
    virtual void translada(double dx, double dy) = 0;
    virtual QPointF centro() const = 0;
    virtual void escala(double sx, double sy, double cx, double cy) = 0;
    virtual void rotaciona(double angGraus, double cx, double cy) = 0;

    void escalaNoCentro(double sx, double sy) {
        QPointF c = centro();
        escala(sx, sy, c.x(), c.y());
    }
    void rotacionaNoCentro(double angGraus) {
        const QPointF c = centro();
        rotaciona(angGraus, c.x(), c.y());
    }

    static inline void rotatePoint(double& x, double& y, double angGraus, double cx, double cy) {
        const double th = qDegreesToRadians(angGraus);
        const double cosT = qCos(th), sinT = qSin(th);
        const double dx = x - cx, dy = y - cy;
        const double xr =  cx + (dx * cosT - dy * sinT);
        const double yr =  cy + (dx * sinT + dy * cosT);
        x = xr; y = yr;
    }
};

class Meu_Ponto : public Meu_Objeto
{
    std::string nome;
public:
    double x, y;

    Meu_Ponto(std::string n, double x_, double y_) : nome(std::move(n)), x(x_), y(y_) {}
    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy) override { x += dx; y += dy; }

    QPointF centro() const override { return QPointF(x, y); }
    void escala(double sx, double sy, double cx, double cy) override {
        x = cx + sx * (x - cx);
        y = cy + sy * (y - cy);
    }
    void rotaciona(double angGraus, double cx, double cy) override {
        rotatePoint(x, y, angGraus, cx, cy);
    }
};


class Minha_Linha : public Meu_Objeto {
    std::string nome;
public:
    Meu_Ponto p1, p2;

    Minha_Linha(std::string n, double x1, double y1, double x2, double y2)
        : nome(std::move(n)), p1("p1", x1, y1), p2("p2", x2, y2) {}

    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy) override { p1.translada(dx,dy); p2.translada(dx,dy); }

    QPointF centro() const override {
        return QPointF((p1.x + p2.x)/2.0, (p1.y + p2.y)/2.0);
    }

    void escala(double sx, double sy, double cx, double cy) override {
        p1.escala(sx, sy, cx, cy);
        p2.escala(sx, sy, cx, cy);
    }
    void rotaciona(double angGraus, double cx, double cy) override {
        rotatePoint(p1.x, p1.y, angGraus, cx, cy);
        rotatePoint(p2.x, p2.y, angGraus, cx, cy);
    }
};


class Minha_Face : public Meu_Objeto {
    std::string nome;
public:
    std::vector<Minha_Linha> arestas;

    explicit Minha_Face(std::string n) : nome(std::move(n)) {}

    void addLinha(double x1, double y1, double x2, double y2) {
        arestas.emplace_back("aresta", x1, y1, x2, y2);
    }

    const std::string& getNome() const override { return nome; }
    void translada(double dx, double dy) override {
        for (auto& a : arestas) a.translada(dx, dy);
    }

    QPointF centro() const override {
        double sx = 0.0, sy = 0.0; int n = 0;
        for (const auto& a : arestas) {
            sx += a.p1.x; sy += a.p1.y; ++n;
            sx += a.p2.x; sy += a.p2.y; ++n;
        }
        if (n == 0) return QPointF(0,0);
        return QPointF(sx/n, sy/n);
    }

    void escala(double sx, double sy, double cx, double cy) override {
        for (auto& a : arestas) {
            a.p1.escala(sx, sy, cx, cy);
            a.p2.escala(sx, sy, cx, cy);
        }
    }
    void rotaciona(double angGraus, double cx, double cy) override {
        for (auto& a : arestas) {
            rotatePoint(a.p1.x, a.p1.y, angGraus, cx, cy);
            rotatePoint(a.p2.x, a.p2.y, angGraus, cx, cy);
        }
    }
};

#endif // MEU_OBJETO_H
