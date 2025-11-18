#include "clipping.h"
#include <algorithm>


double Recorte::x_min = 0;
double Recorte::y_min = 0;
double Recorte::x_max = 800;
double Recorte::y_max = 600;

void Recorte::definirLimites(double xMin, double yMin, double xMax, double yMax) {
    x_min = std::min(xMin, xMax);
    x_max = std::max(xMin, xMax);
    y_min = std::min(yMin, yMax);
    y_max = std::max(yMin, yMax);
}

int Recorte::calcularCodigo(double x, double y) {
    int codigo = DENTRO;

    if (x < x_min)      codigo |= ESQUERDA;
    else if (x > x_max) codigo |= DIREITA;

    if (y < y_min)      codigo |= BAIXO;
    else if (y > y_max) codigo |= CIMA;

    return codigo;
}

Recorte::ResultadoRecorte Recorte::recortarLinhaCohenSutherland(QPointF& p1, QPointF& p2) {
    int codigo1 = calcularCodigo(p1.x(), p1.y());
    int codigo2 = calcularCodigo(p2.x(), p2.y());
    bool aceito = false;

    while (true) {
        if ((codigo1 | codigo2) == DENTRO) {
            aceito = true;
            return (aceito && codigo1 == 0 && codigo2 == 0) ? ACEITAR_TRIVIAL : ACEITAR_RECORTADO;
        } else if (codigo1 & codigo2) {
            return REJEITAR;
        } else {
            double x = 0, y = 0;
            int codigoFora = (codigo1 != DENTRO) ? codigo1 : codigo2;


            if (codigoFora & CIMA) {
                x = p1.x() + (p2.x() - p1.x()) * (y_max - p1.y()) / (p2.y() - p1.y());
                y = y_max;
            } else if (codigoFora & BAIXO) {
                x = p1.x() + (p2.x() - p1.x()) * (y_min - p1.y()) / (p2.y() - p1.y());
                y = y_min;
            } else if (codigoFora & DIREITA) {
                y = p1.y() + (p2.y() - p1.y()) * (x_max - p1.x()) / (p2.x() - p1.x());
                x = x_max;
            } else if (codigoFora & ESQUERDA) {
                y = p1.y() + (p2.y() - p1.y()) * (x_min - p1.x()) / (p2.x() - p1.x());
                x = x_min;
            }

            if (codigoFora == codigo1) {
                p1.setX(x); p1.setY(y);
                codigo1 = calcularCodigo(p1.x(), p1.y());
            } else {
                p2.setX(x); p2.setY(y);
                codigo2 = calcularCodigo(p2.x(), p2.y());
            }
            aceito = true;
        }
    }
    return aceito ? ACEITAR_RECORTADO : REJEITAR;
}
