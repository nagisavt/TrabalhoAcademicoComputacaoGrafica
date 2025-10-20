#include "display_file.h"

void DisplayFile::insertInicio(Meu_Objeto* obj)
{
    Node* novo = new Node(obj);
    novo->setProx(cabeca);
    cabeca = novo;
}
