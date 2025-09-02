#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //PONTOS
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p1",50, 50));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p2", 0, 0));

    //LINHAS
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("p2",10,10,50,100));

    //POLIGONOS
    Minha_Face* triangulo = new Minha_Face("f1");
    triangulo->addLinha(150, 40, 250, 100);
    triangulo->addLinha(250, 100, 200,150);
    triangulo->addLinha(200, 150,150,40);
    ui->Mundo->displayFile.insertInicio(triangulo);

    Minha_Face* estrela = new Minha_Face("f2");
    estrela->addLinha(-200, 20, -271, -197);
    estrela->addLinha(-271, -197, -86, -63);
    estrela->addLinha(-86, -63, -314, -63);
    estrela->addLinha(-314, -63, -129, -197);
    estrela->addLinha(-129, -197, -200, 20);
    ui->Mundo->displayFile.insertInicio(estrela);

}

MainWindow::~MainWindow()
{
    delete ui;
}
