#ifndef MEU_FRAME_H
#define MEU_FRAME_H

#include <iostream>
#include <QFrame>
#include <QWidget>
#include <QPaintEvent>
#include <QRect>
#include <QObject>
#include <QPainter>
#include <string>
#include <vector>

class Meu_Objeto
{
public:
    virtual ~Meu_Objeto() = default;
};

class Meu_Ponto : public Meu_Objeto
{
public:
    std::string nome;
    double x;
    double y;

    Meu_Ponto(const std::string& nome, double x, double y) : nome(nome), x(x), y(y) {}

    Meu_Ponto(double x, double y) : nome(""), x(x), y(y) {}

};


class Minha_Linha : public Meu_Objeto
{
public:
    std::string nome;
    Meu_Ponto p1;
    Meu_Ponto p2;

    Minha_Linha(const std::string& nome, double x1, double y1, double x2, double y2)
        : nome(nome), p1(x1, y1), p2(x2, y2) {}


    Minha_Linha(double x1, double y1, double x2, double y2)
        : nome(""), p1(x1, y1), p2(x2, y2) {}
};


class Minha_Face : public Meu_Objeto
{
public:
    std::string nome;
    std::vector<Minha_Linha> arestas;

    Minha_Face(const std::string& nome)
        : nome(nome) {}

    Minha_Face()
        : nome("") {}

    void addLinha(double x1, double y1, double x2, double y2);
};

class Node
{
private:
    Meu_Objeto* obj;
    Node* prox;
public:
    Node(Meu_Objeto *ptr) : obj(ptr), prox(nullptr) {}

    Meu_Objeto* getObj();
    Node* getProx();
    void setProx(Node* obj);

};

class DisplayFile{
private:
    Node* cabeca;
public:
    DisplayFile()
    {
        cabeca = NULL;
    }
    ~DisplayFile();
    void insertInicio(Meu_Objeto* obj);
    Node* getCabeca();
};

class Meu_frame : public QFrame
{
    Q_OBJECT

private:
    void desenharDisplayFile(QPainter& painter);
public:
    DisplayFile displayFile;
    explicit Meu_frame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

public slots:

    void desenhar();
};

#endif // MEU_FRAME_H










