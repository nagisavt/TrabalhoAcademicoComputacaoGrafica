#include "meu_frame.h"
#include <QPainter>
#include <iostream>
#include "clipping.h"
#include <QMatrix4x4>

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

    QMatrix4x4 matView = window.getViewMatrix();

    QMatrix4x4 matViewport;
    matViewport.translate(width() / 2.0, height() / 2.0, 0);
    matViewport.scale(width() / 2.0, height() / 2.0, 1.0);

    Node* noAtual = displayFile.getCabeca();

    auto transformarPonto = [&](double x, double y, double z) -> QPointF {
        QVector3D p_mundo(x, y, z);

        QVector3D p_view = matView * p_mundo;

        QPointF p_projetado;

        if (m_projecao == TipoProjecao::XY) {
            p_projetado = QPointF(p_view.x(), p_view.y());
        } else if (m_projecao == TipoProjecao::XZ) {
            p_projetado = QPointF(p_view.x(), p_view.z());
        } else if (m_projecao == TipoProjecao::YZ) {
            p_projetado = QPointF(p_view.y(), p_view.z());
        } else {
            double fator = 1.0 + (p_view.z() / d);
            if(fator==0) fator = 0.0001;
            p_projetado = QPointF(p_view.x() / fator, p_view.y() / fator);
        }

        QVector3D p_tela_vec = matViewport * QVector3D(p_projetado.x(), p_projetado.y(), 0);
        return QPointF(p_tela_vec.x(), p_tela_vec.y());
    };

    while (noAtual != nullptr) {
        Meu_Objeto* obj = noAtual->getObj();

        if (Meu_Ponto* ponto = dynamic_cast<Meu_Ponto*>(obj)) {
            QPointF p_tela = transformarPonto(ponto->x, ponto->y, ponto->z);
            if (p_tela.x() >= 0 && p_tela.x() <= width() &&
                p_tela.y() >= 0 && p_tela.y() <= height()) {

                painter.setPen(QPen(Qt::blue, 5));
                painter.drawPoint(p_tela);
            }
        }
        else if (Minha_Linha* linha = dynamic_cast<Minha_Linha*>(obj)) {
            QPointF p1_tela = transformarPonto(linha->p1.x, linha->p1.y, linha->p1.z);
            QPointF p2_tela = transformarPonto(linha->p2.x, linha->p2.y, linha->p2.z);

            Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(p1_tela, p2_tela, 0.0, 0.0, (double)width(), (double)height());

            if (res != Recorte::REJEITAR) {
                if (res == Recorte::ACEITAR_RECORTADO) painter.setPen(QPen(Qt::red, 2));
                else painter.setPen(QPen(Qt::green, 2));

                painter.drawLine(p1_tela, p2_tela);
            }
        }
        else if (Minha_Face* face = dynamic_cast<Minha_Face*>(obj)) {
            for (const auto& aresta : face->arestas) {
                QPointF p1_tela = transformarPonto(aresta.p1.x, aresta.p1.y, aresta.p1.z);
                QPointF p2_tela = transformarPonto(aresta.p2.x, aresta.p2.y, aresta.p2.z);

                Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(p1_tela, p2_tela, 0.0, 0.0, (double)width(), (double)height());

                if (res != Recorte::REJEITAR) {
                    if (res == Recorte::ACEITAR_RECORTADO) painter.setPen(QPen(Qt::red, 2));
                    else painter.setPen(QPen(Qt::white, 2));

                    painter.drawLine(p1_tela, p2_tela);
                }
            }
        }
        noAtual = noAtual->getProx();
    }

    painter.restore();
}

