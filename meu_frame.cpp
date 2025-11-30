#include "meu_frame.h"
#include <QPainter>
#include <QPointF>
#include "clipping.h"
#include "Mat.h"

using namespace std;

Meu_frame::Meu_frame(QWidget *parent) :QFrame{parent} {}

void Meu_frame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    desenharDisplayFile(painter);
}

void Meu_frame::desenhar(){
    update();
}

void Meu_frame::desenharDisplayFile(QPainter& painter) {
    painter.save();

    Matriz4x4 matView = window.getViewMatriz();
    Matriz4x4 matProj = identidade();

    if(m_projecao == TipoProjecao::PERSPECTIVA){
        matProj = matrizPerspectiva(this->d);
    }

    Matriz4x4 matViewPort = matrizViewport(width(), height());

    Node* noAtual = displayFile.getCabeca();

    auto transformarParaTela = [&](double x, double y, double z) -> QPointF {

        ponto4D p(x, y, z, 1.0);

        p = transformarPonto(matView, p);

        if (m_projecao == TipoProjecao::PERSPECTIVA) {
            p = transformarPonto(matProj, p);
            if (std::abs(p.w) > 0.00001) {
                double fator = std::abs(p.w);
                p.x /= fator;
                p.y /= fator;
                p.z /= fator;
                p.w = 1.0;
            }
        }else{
            if (m_projecao == TipoProjecao::XY) { p.z = 0; }
            else if (m_projecao == TipoProjecao::XZ) { p.y = 0; }
            else if (m_projecao == TipoProjecao::YZ) { p.x = 0; }
        }

        p = transformarPonto(matViewPort, p);

        return QPointF(p.x, p.y);
    };

    while (noAtual != nullptr) {
        Meu_Objeto* obj = noAtual->getObj();

        if(Meu_Ponto* ponto = dynamic_cast<Meu_Ponto*>(obj)){
           QPointF pTela = transformarParaTela(ponto->x, ponto->y, ponto->z);
            if(pTela.x() >= 0 && pTela.x() <= width() &&
               pTela.y() >= 0 && pTela.y() <= height()){
                painter.setPen(QPen(Qt::blue, 5));
                painter.drawPoint(pTela);
            }
        }else if(Minha_Linha* linha = dynamic_cast<Minha_Linha*>(obj)){
            QPointF pTela1 = transformarParaTela(linha->p1.x, linha->p1.y, linha->p1.z);
            QPointF pTela2 = transformarParaTela(linha->p2.x, linha->p2.y, linha->p2.z);

            Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(pTela1, pTela2, 0.0, 0.0, (double)width(), (double)height());

            if (res != Recorte::REJEITAR) {
                if (res == Recorte::ACEITAR_RECORTADO) painter.setPen(QPen(Qt::red, 2));
                else painter.setPen(QPen(Qt::green, 2));

                painter.drawLine(pTela1, pTela2);
            }
        }else if(Minha_Face* face = dynamic_cast<Minha_Face*>(obj)){
            for (const auto& aresta : face->arestas){
                QPointF pTela1 = transformarParaTela(aresta.p1.x, aresta.p1.y, aresta.p1.z);
                QPointF pTela2 = transformarParaTela(aresta.p2.x, aresta.p2.y, aresta.p2.z);

                Recorte::ResultadoRecorte res = Recorte::recortarLinhaCohenSutherland(pTela1, pTela2, 0.0, 0.0, (double)width(), (double)height());

                if (res != Recorte::REJEITAR) {
                    if (res == Recorte::ACEITAR_RECORTADO) painter.setPen(QPen(Qt::red, 2));
                    else painter.setPen(QPen(Qt::green, 2));

                    painter.drawLine(pTela1, pTela2);
                }
            }
        }
        noAtual = noAtual->getProx();
    }
    painter.restore();
};

