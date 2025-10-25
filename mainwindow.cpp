#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meu_frame.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // CHAO
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("chao", -500, 0, 0,500, 0, 0));


    // CASA
    // Base
    Minha_Face* casaBase = new Minha_Face("casa_base");
    casaBase->addLinha(100, 0, 0,300, 0, 0);   // Chão da casa
    casaBase->addLinha(300, 0, 0,300, 200, 0); // Parede direita
    casaBase->addLinha(300, 200, 0,100, 200, 0); // Teto (base do telhado)
    casaBase->addLinha(100, 200, 0,100, 0, 0);   // Parede esquerda
    ui->Mundo->displayFile.insertInicio(casaBase);

    // Telhado
    Minha_Face* telhado = new Minha_Face("casa_telhado");
    telhado->addLinha(100, 200, 0,300, 200, 0);
    telhado->addLinha(300, 200, 0,200, 280, 0); // Ponta do telhado
    telhado->addLinha(200, 280, 0, 100, 200, 0);
    ui->Mundo->displayFile.insertInicio(telhado);

    // Porta
    Minha_Face* porta = new Minha_Face("casa_porta");
    porta->addLinha(130, 0, 0, 170, 0, 0);
    porta->addLinha(170, 0, 0, 170, 120, 0);
    porta->addLinha(170, 120, 0, 130, 120, 0);
    porta->addLinha(130, 120, 0, 130, 0, 0);
    ui->Mundo->displayFile.insertInicio(porta);

    // Janela
    Minha_Face* janela = new Minha_Face("casa_janela");
    janela->addLinha(220, 80, 0, 280, 80, 0);
    janela->addLinha(280, 80, 0, 280, 140, 0);
    janela->addLinha(280, 140, 0, 220, 140, 0);
    janela->addLinha(220, 140, 0, 220, 80, 0);
    ui->Mundo->displayFile.insertInicio(janela);

    // Vidros
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("janela_vidro_v", 250, 80, 0, 250, 140, 0)); // Vertical
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("janela_vidro_h", 220, 110, 0, 280, 110, 0)); // Horizontal


    // arvore
    // Tronco
    Minha_Face* tronco = new Minha_Face("arvore_tronco");
    tronco->addLinha(-150, 0, 0, -120, 0, 0);
    tronco->addLinha(-120, 0, 0, -120, 100, 0);
    tronco->addLinha(-120, 100, 0, -150, 100, 0);
    tronco->addLinha(-150, 100, 0, -150, 0, 0);
    ui->Mundo->displayFile.insertInicio(tronco);

    //folhas
    Minha_Face* copa = new Minha_Face("arvore_copa");
    copa->addLinha(-180, 100, 0, -200, 150, 0);
    copa->addLinha(-200, 150, 0, -135, 220, 0); // Topo da árvore
    copa->addLinha(-135, 220, 0, -70, 150, 0);
    copa->addLinha(-70, 150, 0, -90, 100, 0);
    copa->addLinha(-90, 100, 0, -180, 100, 0);
    ui->Mundo->displayFile.insertInicio(copa);

    // ceu
    // Lua
    Minha_Face* lua = new Minha_Face("lua");
    lua->addLinha(-430, 400, 0, -421, 421, 0);
    lua->addLinha(-421, 421, 0, -400, 430, 0);
    lua->addLinha(-400, 430, 0, -379, 421, 0);
    lua->addLinha(-379, 421, 0, -370, 400, 0);
    lua->addLinha(-370, 400, 0, -379, 379, 0);
    lua->addLinha(-379, 379, 0, -400, 370, 0);
    lua->addLinha(-400, 370, 0, -421, 379, 0);
    lua->addLinha(-421, 379, 0, -430, 400, 0);
    ui->Mundo->displayFile.insertInicio(lua);

    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("estrela1", -300, 350, 0));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("estrela2", -100, 400, 0));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("estrela3", 50, 450, 0));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("estrela4", 400, 380, 0));

    preencherListaObjetos();

    connect(ui->btnTransladar, &QPushButton::clicked, this, &MainWindow::on_btnTransladar_clicked);
    connect(ui->btnEscalar, &QPushButton::clicked, this, &MainWindow::on_btnEscalar_clicked);
    connect(ui->btnRotacionar, &QPushButton::clicked, this, &MainWindow::on_btnRotacionar_clicked);

}

void MainWindow::preencherListaObjetos() {
    ui->comboObjetos->clear();
    auto nomes = ui->Mundo->displayFile.listNames();
    for (const auto& n : nomes) {
        ui->comboObjetos->addItem(QString::fromStdString(n));
    }
}

void MainWindow::on_btnTransladar_clicked() {
    const QString sel = ui->comboObjetos->currentText();
    if (sel.isEmpty()) return;

    const double dx = ui->spinDx->value();
    const double dy = ui->spinDy->value();
    Meu_Objeto* obj = ui->Mundo->displayFile.findByName(sel.toStdString());
    if (!obj) return;

    obj->translada(dx, dy);

    ui->Mundo->update();
}

void MainWindow::on_btnEscalar_clicked() {
    const QString sel = ui->comboObjetos->currentText();
    if (sel.isEmpty()) return;

    const double sx = ui->spinSx->value();
    const double sy = ui->spinSy->value();
    if (sx == 0.0 || sy == 0.0) return;

    Meu_Objeto* obj = ui->Mundo->displayFile.findByName(sel.toStdString());
    if (!obj) return;
    obj->escalaNoCentro(sx, sy);

    ui->Mundo->update();
}

void MainWindow::on_btnRotacionar_clicked() {
    const QString sel = ui->comboObjetos->currentText();
    if (sel.isEmpty()) return;

    double ang = ui->spinAng->value();

    Meu_Objeto* obj = ui->Mundo->displayFile.findByName(sel.toStdString());
    if (!obj) return;
    obj->rotacionaNoCentro(ang);

    ui->Mundo->update();
}

void MainWindow::on_btnPanCima_clicked()
{
    ui->Mundo->getWindow().pan(0, 25.0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanBaixo_clicked()
{
    ui->Mundo->getWindow().pan(0, -25.0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanEsquerda_clicked()
{
    ui->Mundo->getWindow().pan(-25.0, 0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanDireita_clicked()
{
    ui->Mundo->getWindow().pan(25.0, 0);
    ui->Mundo->update();
}


// SLOTS PARA CONTROLE DE ZOOM

void MainWindow::on_btnZoomIn_clicked()
{
    const double fatorZoom = 0.9;
    ui->Mundo->getWindow().zoom(fatorZoom);
    ui->Mundo->update();
}

void MainWindow::on_btnZoomOut_clicked()
{
    const double fatorZoom = 1.1;
    ui->Mundo->getWindow().zoom(fatorZoom);
    ui->Mundo->update();
}


// SLOTS PARA CONTROLE DE ROTAÇÃO DA CÂMERA

void MainWindow::on_btnGirarHorario_clicked()
{
    const double angulo = -5.0;
    ui->Mundo->getWindow().rotate(angulo);
    ui->Mundo->update();
}

void MainWindow::on_btnGirarAntiHorario_clicked()
{
    const double angulo = 5.0;
    ui->Mundo->getWindow().rotate(angulo);
    ui->Mundo->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}
