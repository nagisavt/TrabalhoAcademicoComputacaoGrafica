#ifndef CLIPPING_H
#define CLIPPING_H

#include <QPointF>

namespace Recorte {

const int DENTRO = 0;   // 0000
const int ESQUERDA = 1; // 0001
const int DIREITA  = 2; // 0010
const int BAIXO = 4;    // 0100
const int CIMA = 8;     // 1000

inline int calcularCodigo(double x, double y, double xMin, double yMin, double xMax, double yMax) {
    int codigo = DENTRO;

    if (x < xMin)
        codigo |= ESQUERDA;
    else if (x > xMax)
        codigo |= DIREITA;

    if (y < yMin)
        codigo |= BAIXO;
    else if (y > yMax)
        codigo |= CIMA;

    return codigo;
}

inline int calcularCodigo(QPointF p, double xMin, double yMin, double xMax, double yMax) {
    return calcularCodigo(p.x(), p.y(), xMin, yMin, xMax, yMax);
}

enum ResultadoRecorte {
    REJEITAR,
    ACEITAR_TRIVIAL,
    ACEITAR_RECORTADO
};

inline ResultadoRecorte recortarLinhaCohenSutherland(QPointF& p1, QPointF& p2, double xMin, double yMin, double xMax, double yMax) {
    int codigo1 = calcularCodigo(p1, xMin, yMin, xMax, yMax);
    int codigo2 = calcularCodigo(p2, xMin, yMin, xMax, yMax);
    bool foiRecortado = false;

    while (true) {
        if ((codigo1 | codigo2) == DENTRO) {
            if (foiRecortado) return ACEITAR_RECORTADO;
            else return ACEITAR_TRIVIAL;

        } else if ((codigo1 & codigo2) != DENTRO) {
            return REJEITAR;
        } else {
            foiRecortado = true;

            int codigoFora = (codigo1 != DENTRO) ? codigo1 : codigo2;
            double x = 0.0, y = 0.0;
            double x1 = p1.x(), y1 = p1.y();
            double x2 = p2.x(), y2 = p2.y();

            if (codigoFora & CIMA) {
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                y = yMax;
            } else if (codigoFora & BAIXO) {
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                y = yMin;
            } else if (codigoFora & DIREITA) {
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                x = xMax;
            } else if (codigoFora & ESQUERDA) {
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                x = xMin;
            }

            if (codigoFora == codigo1) {
                p1.setX(x); p1.setY(y);
                codigo1 = calcularCodigo(p1, xMin, yMin, xMax, yMax);
            } else {
                p2.setX(x); p2.setY(y);
                codigo2 = calcularCodigo(p2, xMin, yMin, xMax, yMax);
            }
        }
    }
}

} // namespace Recorte

#endif // CLIPPING_H
