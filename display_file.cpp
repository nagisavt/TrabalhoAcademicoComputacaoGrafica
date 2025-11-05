#include "display_file.h"

void DisplayFile::insertInicio(Meu_Objeto* obj)
{
    Node* novo = new Node(obj);
    novo->setProx(cabeca);
    cabeca = novo;
}

DisplayFile::~DisplayFile()
{
    Node* atual = cabeca;
    while (atual != nullptr) {
        Node* prox = atual->getProx();
        delete atual->getObj();
        delete atual;
        atual = prox;
    }
}
