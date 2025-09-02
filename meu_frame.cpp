#include "meu_frame.h"
#include <QPainter>

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
    QTransform T;
    T.translate(width()/2.0, height()/2.0);
    T.scale(1.0, -1.0);
    painter.setWorldTransform(T);

    Node* noAtual = displayFile.getCabeca();
    if(!noAtual){
        cout<<"DisplayFile vazia..."<<endl;
        return;
    }
    cout <<"Desanhando objetos..."<<endl;

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
            painter.setPen(QPen(Qt::red, 2));
            for(auto it = face->arestas.begin();it != face->arestas.end(); it++){
                painter.setPen(QPen(Qt::red, 2));
                painter.drawLine(it->p1.x, it->p1.y, it->p2.x, it->p2.y);
            }
        }
        noAtual = noAtual->getProx();
    }
    painter.restore();
 }

void Minha_Face::addLinha(double x1, double y1, double x2, double y2)
{
    arestas.push_back(Minha_Linha(x1, y1, x2, y2));
}

Meu_Objeto* Node::getObj()
{
    return obj;
}

Node* Node::getProx(){
    return prox;
}

void Node::setProx(Node* obj){
    prox = obj;
}

Node* DisplayFile::getCabeca(){
    return cabeca;
}

DisplayFile::~DisplayFile(){
    Node* atual = cabeca;
    while(atual != nullptr){
        Node* proximo = atual->getProx();
        delete atual->getObj();
        delete atual;
        atual = proximo;
    }
}

void DisplayFile::insertInicio(Meu_Objeto* obj)
{
    Node* novo = new Node(obj);
    novo->setProx(cabeca);
    cabeca = novo;
}

