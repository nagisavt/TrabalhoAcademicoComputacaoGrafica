#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meu_frame.h"
#include <QDebug>
#include "read_obj.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Mundo->displayFile.insertInicio(new Minha_Linha("chao", -500, 0, 0, 500, 0, 0));

    Minha_Face* casa3D = new Minha_Face("casa_3d");

    double zFrente = 0.0;
    double zFundo = 200.0; // Profundidade da casa

    // --- PAREDES (CUBO) ---

    // Face Frontal (Z = 0)
    casa3D->addLinha(100, 0, zFrente, 300, 0, zFrente);     // Chão
    casa3D->addLinha(300, 0, zFrente, 300, 200, zFrente);   // Dir
    casa3D->addLinha(300, 200, zFrente, 100, 200, zFrente); // Teto
    casa3D->addLinha(100, 200, zFrente, 100, 0, zFrente);   // Esq

    // Face Traseira (Z = 200)
    casa3D->addLinha(100, 0, zFundo, 300, 0, zFundo);       // Chão
    casa3D->addLinha(300, 0, zFundo, 300, 200, zFundo);     // Dir
    casa3D->addLinha(300, 200, zFundo, 100, 200, zFundo);   // Teto
    casa3D->addLinha(100, 200, zFundo, 100, 0, zFundo);     // Esq

    // Conexões (Laterais que ligam frente ao fundo)
    casa3D->addLinha(100, 0, zFrente, 100, 0, zFundo);      // Rodapé Esq
    casa3D->addLinha(300, 0, zFrente, 300, 0, zFundo);      // Rodapé Dir
    casa3D->addLinha(300, 200, zFrente, 300, 200, zFundo);  // Calha Dir
    casa3D->addLinha(100, 200, zFrente, 100, 200, zFundo);  // Calha Esq


    // --- TELHADO (PRISMA TRIANGULAR) ---

    // Triângulo Frente
    casa3D->addLinha(100, 200, zFrente, 200, 300, zFrente); // Subida
    casa3D->addLinha(200, 300, zFrente, 300, 200, zFrente); // Descida

    // Triângulo Fundo
    casa3D->addLinha(100, 200, zFundo, 200, 300, zFundo);   // Subida
    casa3D->addLinha(200, 300, zFundo, 300, 200, zFundo);   // Descida

    // Conexão do Cume (Topo do telhado)
    casa3D->addLinha(200, 300, zFrente, 200, 300, zFundo);

    // Inserir na lista
    ui->Mundo->displayFile.insertInicio(casa3D);
    casa3D->translada(0,0,-60);

    // =========================================================
    // 5. ÁRVORE (Tronco + Copa)
    // =========================================================
    Minha_Face* arvore = new Minha_Face("arvore");

    // Posição da árvore (ao lado da casa)
    double ax = -200, az = 50;

    // --- Tronco (Prisma retangular alto) ---
    double largTronco = 30;
    double altTronco = 150;
    double zTronco = largTronco; // Tronco quadrado na base

    // Coordenadas baseadas no centro (ax, az)
    double tX1 = ax,           tZ1 = az;
    double tX2 = ax + largTronco, tZ2 = az + zTronco;

    // Base do Tronco (y=0)
    arvore->addLinha(tX1, 0, tZ1, tX2, 0, tZ1);
    arvore->addLinha(tX2, 0, tZ1, tX2, 0, tZ2);
    arvore->addLinha(tX2, 0, tZ2, tX1, 0, tZ2);
    arvore->addLinha(tX1, 0, tZ2, tX1, 0, tZ1);

    // Topo do Tronco (y=altTronco)
    arvore->addLinha(tX1, altTronco, tZ1, tX2, altTronco, tZ1);
    arvore->addLinha(tX2, altTronco, tZ1, tX2, altTronco, tZ2);
    arvore->addLinha(tX2, altTronco, tZ2, tX1, altTronco, tZ2);
    arvore->addLinha(tX1, altTronco, tZ2, tX1, altTronco, tZ1);

    // Conexões Verticais do Tronco
    arvore->addLinha(tX1, 0, tZ1, tX1, altTronco, tZ1);
    arvore->addLinha(tX2, 0, tZ1, tX2, altTronco, tZ1);
    arvore->addLinha(tX2, 0, tZ2, tX2, altTronco, tZ2);
    arvore->addLinha(tX1, 0, tZ2, tX1, altTronco, tZ2);


    // --- Copa (Pirâmide ou Cubo sobre o tronco) ---
    // Vamos fazer uma Pirâmide para variar
    double copaBaseY = altTronco;
    double copaAlt = 100;
    double copaLarg = 100; // Mais larga que o tronco

    // Centro da copa
    double cx = ax + largTronco/2;
    double cz = az + zTronco/2;

    // 4 Pontos da base da pirâmide
    double cX1 = cx - copaLarg/2; double cZ1 = cz - copaLarg/2;
    double cX2 = cx + copaLarg/2; double cZ2 = cz + copaLarg/2;

    // Base da Copa
    arvore->addLinha(cX1, copaBaseY, cZ1, cX2, copaBaseY, cZ1); // Frente
    arvore->addLinha(cX2, copaBaseY, cZ1, cX2, copaBaseY, cZ2); // Dir
    arvore->addLinha(cX2, copaBaseY, cZ2, cX1, copaBaseY, cZ2); // Fundo
    arvore->addLinha(cX1, copaBaseY, cZ2, cX1, copaBaseY, cZ1); // Esq

    // Ponta da Pirâmide (Topo)
    double pX = cx;
    double pY = copaBaseY + copaAlt;
    double pZ = cz;

    // Ligar base ao topo
    arvore->addLinha(cX1, copaBaseY, cZ1, pX, pY, pZ);
    arvore->addLinha(cX2, copaBaseY, cZ1, pX, pY, pZ);
    arvore->addLinha(cX2, copaBaseY, cZ2, pX, pY, pZ);
    arvore->addLinha(cX1, copaBaseY, cZ2, pX, pY, pZ);

    ui->Mundo->displayFile.insertInicio(arvore);
    arvore->translada(0,0,-60);

    Minha_Face* umbreon = m_objloader.loadObj("UmbreonLowPoly.obj");
    if(umbreon){
        ui->Mundo->displayFile.insertInicio(umbreon);
    } else {
        qDebug() << "Não foi possivel criar UmbreonLowPoly.obj";
    }
    umbreon->escalaNoCentro(10,10,10);
    umbreon->translada(-10,40,-20);

    Minha_Face* gengar = m_objloader.loadObj("HAUNTER_pokemon.obj");
    if(gengar){
        ui->Mundo->displayFile.insertInicio(gengar);
    } else {
        qDebug() << "Não foi possivel criar HAUNTER_pokemon.obj";
    }
    gengar->escalaNoCentro(0.8,0.8,0.8);
    gengar->translada(20,20,10);

    preencherListaObjetos();
}

MainWindow::~MainWindow() {
    delete ui;
}

Meu_Objeto* MainWindow::getObjetoSelecionado() {
    const QString sel = ui->comboObjetos->currentText();
    if (sel.isEmpty()) return nullptr;
    return ui->Mundo->displayFile.findByName(sel.toStdString());
}

void MainWindow::preencherListaObjetos() {
    ui->comboObjetos->clear();
    auto nomes = ui->Mundo->displayFile.listNames();
    for (const auto& n : nomes) {
        ui->comboObjetos->addItem(QString::fromStdString(n));
    }
}

void MainWindow::on_btnTransladar_clicked() {
    Meu_Objeto* obj = getObjetoSelecionado();
    if (!obj) return;
    const double dx = ui->spinDx->value();
    const double dy = ui->spinDy->value();
    const double dz = ui->spinDz->value();
    obj->translada(dx, dy, dz);
    ui->Mundo->update();
}

void MainWindow::on_btnEscalar_clicked() {
    Meu_Objeto* obj = getObjetoSelecionado();
    if (!obj) return;
    const double sx = ui->spinSx->value();
    const double sy = ui->spinSy->value();
    const double sz = ui->spinSz->value();
    if (sx == 0.0 || sy == 0.0) return;
    obj->escalaNoCentro(sx, sy, sz);
    ui->Mundo->update();
}

void MainWindow::on_btnRotacionarX_clicked() {
    Meu_Objeto* obj = getObjetoSelecionado();
    if (!obj) return;
    double ang = ui->spinAng->value();
    obj->rotacionaXNoCentro(ang);
    ui->Mundo->update();
}

void MainWindow::on_btnRotacionarY_clicked() {
    Meu_Objeto* obj = getObjetoSelecionado();
    if (!obj) return;
    double ang = ui->spinAng->value();
    obj->rotacionaYNoCentro(ang);
    ui->Mundo->update();
}

void MainWindow::on_btnRotacionarZ_clicked() {
    Meu_Objeto* obj = getObjetoSelecionado();
    if (!obj) return;
    double ang = ui->spinAng->value();
    obj->rotacionaZNoCentro(ang);
    ui->Mundo->update();
}

void MainWindow::on_btnAntiX_clicked() {
    ui->Mundo->getWindow().rotateX(5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnHorX_clicked() {
    ui->Mundo->getWindow().rotateX(-5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnAntiY_clicked() {
    ui->Mundo->getWindow().rotateY(5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnHorY_clicked() {
    ui->Mundo->getWindow().rotateY(-5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnAntiZ_clicked() {
    ui->Mundo->getWindow().rotateZ(5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnHorZ_clicked() {
    ui->Mundo->getWindow().rotateZ(-5.0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanCima_clicked() {
    ui->Mundo->getWindow().pan(0, 25.0, 0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanBaixo_clicked() {
    ui->Mundo->getWindow().pan(0, -25.0, 0);
    ui->Mundo->desenhar();
}

void MainWindow::on_btnPanEsquerda_clicked() {
    ui->Mundo->getWindow().pan(-25.0, 0, 0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanDireita_clicked() {
    ui->Mundo->getWindow().pan(25.0, 0, 0);
    ui->Mundo->update();
}

void MainWindow::on_btnZoomIn_clicked() {
    ui->Mundo->getWindow().zoom(0.9);
    ui->Mundo->update();
}

void MainWindow::on_btnZoomOut_clicked() {
    ui->Mundo->getWindow().zoom(1.1);
    ui->Mundo->update();
}

void MainWindow::on_btnProjecaoXY_clicked() {
    ui->Mundo->setProjecao(Meu_frame::TipoProjecao::XY);
}

void MainWindow::on_btnProjecaoXZ_clicked() {
    ui->Mundo->setProjecao(Meu_frame::TipoProjecao::XZ);
}

void MainWindow::on_btnProjecaoYZ_clicked() {
    ui->Mundo->setProjecao(Meu_frame::TipoProjecao::YZ);
}

void MainWindow::on_btnProjecaoPerspectiva_clicked() {
    qDebug() << "Mudando para Projeção em Perspectiva";
    ui->Mundo->setProjecao(Meu_frame::TipoProjecao::PERSPECTIVA);
}
