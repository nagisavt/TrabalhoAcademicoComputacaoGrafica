#include "meu_frame.h"
#include <QPainter>
#include <iostream>
#include "clipping.h"

using namespace std;

Meu_frame::Meu_frame(QWidget *parent)
    :QFrame{parent}
{

}

void Meu_frame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    desenharDisplayFile(painter);
}

void Meu_frame::desenhar(){
    cout <<"Desenhando..." << endl;
    update();
}

void Meu_frame::desenharDisplayFile(QPainter& painter) {
    painter.save();

    QTransform T_window = window.getTransformacao();
    QTransform T_viewport;
    T_viewport.translate(width() / 2.0, height() / 2.0);
    T_viewport.scale(width() / 2.0, -height() / 2.0);

    Node* noAtual = displayFile.getCabeca();
    while (noAtual != nullptr) {
        Meu_Objeto* obj = noAtual->getObj();

        if (Meu_Ponto* ponto = dynamic_cast<Meu_Ponto*>(obj)) {
            // Pontos: Vermelho se estiverem dentro, nada se estiverem fora
            painter.setPen(QPen(Qt::red, 8));
            QPointF p_mundo(ponto->x, ponto->y);

            switch(m_projecao){
                case TipoProjecao::XY:
                    p_mundo = QPointF(ponto->x, ponto->y);
                    break;
                case TipoProjecao::XZ:
                    p_mundo = QPointF(ponto->x, ponto->z);
                    break;
                case TipoProjecao::YZ:
                    p_mundo = QPoint(ponto->y, ponto->z);
                    break;
            }

            QPointF p_norm = T_window.map(p_mundo);

            if (Recorte::calcularCodigo(p_norm) == Recorte::DENTRO) {
                QPointF p_tela = T_viewport.map(p_norm);
                painter.drawPoint(p_tela);
            }
        }
        else if (Minha_Linha* linha = dynamic_cast<Minha_Linha*>(obj)) {
            QPointF p1_mundo(linha->p1.x, linha->p1.y);
            QPointF p2_mundo(linha->p2.x, linha->p2.y);

            switch (m_projecao) {
                case TipoProjecao::XY: // Frontal
                    p1_mundo = QPointF(linha->p1.x, linha->p1.y);
                    p2_mundo = QPointF(linha->p2.x, linha->p2.y);
                    break;
                case TipoProjecao::XZ: // Superior
                    p1_mundo = QPointF(linha->p1.x, linha->p1.z);
                    p2_mundo = QPointF(linha->p2.x, linha->p2.z);
                    break;
                case TipoProjecao::YZ: // Lateral
                    p1_mundo = QPointF(linha->p1.z, linha->p1.y);
                    p2_mundo = QPointF(linha->p2.z, linha->p2.y);
                    break;
            }

            QPointF p1_norm = T_window.map(p1_mundo);
            QPointF p2_norm = T_window.map(p2_mundo);

            Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(p1_norm, p2_norm);

            if (res == Recorte::ACEITAR_TRIVIAL) {
                painter.setPen(QPen(Qt::green, 3));
            } else if (res == Recorte::ACEITAR_RECORTADO) {
                painter.setPen(QPen(Qt::red, 3));
            }

            if (res != Recorte::REJEITAR) {
                QPointF p1_tela = T_viewport.map(p1_norm);
                QPointF p2_tela = T_viewport.map(p2_norm);
                painter.drawLine(p1_tela, p2_tela);
            }
        }
        else if (Minha_Face* face = dynamic_cast<Minha_Face*>(obj)) {
            // Faremos a mesma lógica para CADA aresta da face
            for (const auto& aresta : face->vertices) {
                QPointF p1_mundo(aresta.p1.x, aresta.p1.y);
                QPointF p2_mundo(aresta.p2.x, aresta.p2.y);

                switch (m_projecao) {
                    case TipoProjecao::XY: // Frontal
                        p1_mundo = QPointF(linha->p1.x, linha->p1.y);
                        p2_mundo = QPointF(linha->p2.x, linha->p2.y);
                        break;
                    case TipoProjecao::XZ: // Superior
                        p1_mundo = QPointF(linha->p1.x, linha->p1.z);
                        p2_mundo = QPointF(linha->p2.x, linha->p2.z);
                        break;
                    case TipoProjecao::YZ: // Lateral
                        p1_mundo = QPointF(linha->p1.z, linha->p1.y);
                        p2_mundo = QPointF(linha->p2.z, linha->p2.y);
                        break;
                    }

                QPointF p1_norm = T_window.map(p1_mundo);
                QPointF p2_norm = T_window.map(p2_mundo);

                Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(p1_norm, p2_norm);

                if (res == Recorte::ACEITAR_TRIVIAL) {
                    painter.setPen(QPen(Qt::blue, 2));
                } else if (res == Recorte::ACEITAR_RECORTADO) {
                    painter.setPen(QPen(Qt::red, 2));
                }

                if (res != Recorte::REJEITAR) {
                    QPointF p1_tela = T_viewport.map(p1_norm);
                    QPointF p2_tela = T_viewport.map(p2_norm);
                    painter.drawLine(p1_tela, p2_tela);
                }
            }
        }
        noAtual = noAtual->getProx();
    }

    painter.restore();
}

