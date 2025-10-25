#ifndef CLIPPING_H
#define CLIPPING_H

#include <QPointF>

namespace Recorte {

// regioes
const int DENTRO = 0;   // 0000
const int ESQUERDA = 1; // 0001
const int DIREITA  = 2; // 0010
const int BAIXO = 4;    // 0100
const int CIMA = 8;     // 1000

const double X_MIN = -1.0;
const double X_MAX = 1.0;
const double Y_MIN = -1.0;
const double Y_MAX = 1.0;

inline int calcularCodigo(double x, double y) {
    int codigo = DENTRO;

    if (x < X_MIN)
        codigo |= ESQUERDA;
    else if (x > X_MAX)
        codigo |= DIREITA;

    if (y < Y_MIN)
        codigo |= BAIXO;
    else if (y > Y_MAX)
        codigo |= CIMA;

    return codigo;
}

inline int calcularCodigo(QPointF p) {
    return calcularCodigo(p.x(), p.y());
}

enum ResultadoRecorte {
    REJEITAR,
    ACEITAR_TRIVIAL,
    ACEITAR_RECORTADO
};

inline ResultadoRecorte recortarLinhaCohenSutherland(QPointF& p1, QPointF& p2) {
    int codigo1 = calcularCodigo(p1);
    int codigo2 = calcularCodigo(p2);
    bool foiRecortado = false;

    while (true) {
        if ((codigo1 | codigo2) == DENTRO) {
            if (foiRecortado)
                return ACEITAR_RECORTADO;
            else
                return ACEITAR_TRIVIAL;

        } else if ((codigo1 & codigo2) != DENTRO) {
            return REJEITAR;
        } else {
            foiRecortado = true;

            int codigoFora = (codigo1 != DENTRO) ? codigo1 : codigo2;
            double x = 0.0, y = 0.0;
            double x1 = p1.x(), y1 = p1.y();
            double x2 = p2.x(), y2 = p2.y();

            if (codigoFora & CIMA) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codigoFora & BAIXO) {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codigoFora & DIREITA) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (codigoFora & ESQUERDA) {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (codigoFora == codigo1) {
                p1.setX(x);
                p1.setY(y);
                codigo1 = calcularCodigo(p1);
            } else {
                p2.setX(x);
                p2.setY(y);
                codigo2 = calcularCodigo(p2);
            }
        }
    }
}

} // namespace Recorte

#endif // CLIPPING_H
