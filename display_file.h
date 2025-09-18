#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include "meu_objeto.h"

class Node {
    Meu_Objeto* obj = nullptr;
    Node* prox = nullptr;
public:
    explicit Node(Meu_Objeto* o) : obj(o) {}
    Meu_Objeto* getObj() const { return obj; }
    Node* getProx() const { return prox; }
    void setProx(Node* p) { prox = p; }
};

class DisplayFile {
public:
    Node* cabeca = nullptr;
    void insertInicio(Meu_Objeto* obj);

    Node* getCabeca() const { return cabeca; }

    Meu_Objeto* findByName(const std::string& nome) const {
        for (Node* n = cabeca; n; n = n->getProx())
            if (n->getObj() && n->getObj()->getNome() == nome) return n->getObj();
        return nullptr;
    }

    std::vector<std::string> listNames() const {
        std::vector<std::string> v;
        for (Node* n = cabeca; n; n = n->getProx())
            if (n->getObj()) v.push_back(n->getObj()->getNome());
        return v;
    }
};

#endif // DISPLAY_FILE_H
