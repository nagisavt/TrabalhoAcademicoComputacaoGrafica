#include "meu_frame.h"
#include <QPainter>
#include <iostream>

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

void Meu_frame::desenharDisplayFile(QPainter& painter){
    painter.save();

    QTransform T_window = window.getTransformacao();
    QTransform T_viewport;
    T_viewport.scale(width() / 2.0, -height() / 2.0);
    T_viewport.translate(1.0, -1.0);
    QTransform T_final = T_viewport * T_window;
    painter.setWorldTransform(T_final);

    Node* noAtual = displayFile.getCabeca();
    if(!noAtual){
        // cout<<"DisplayFile vazia..."<<endl; // Opcional
        painter.restore();
        return;
    }
    // cout <<"Desanhando objetos..."<<endl; // Opcional

    while (noAtual != nullptr){
        Meu_Objeto* obj = noAtual->getObj();
        if(Meu_Ponto* ponto = dynamic_cast<Meu_Ponto*>(obj)){
            painter.setPen(QPen(Qt::red, 8));
            painter.drawPoint(ponto->x, ponto->y);
        }
        else if(Minha_Linha* linha = dynamic_cast<Minha_Linha*>(obj)){
            painter.setPen(QPen(Qt::black, 3));
            painter.drawLine(linha->p1.x, linha->p1.y, linha->p2.x, linha->p2.y);
        }
        else if(Minha_Face* face = dynamic_cast<Minha_Face*>(obj)){
            painter.setPen(QPen(Qt::blue, 2));
            for(const auto& aresta : face->arestas){
                painter.drawLine(aresta.p1.x, aresta.p1.y, aresta.p2.x, aresta.p2.y);
            }
        }
        noAtual = noAtual->getProx();
    }

    painter.restore();
}


