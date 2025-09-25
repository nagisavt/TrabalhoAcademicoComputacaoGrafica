#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meu_frame.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //PONTOS
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p1",50, 50));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p2", 0, 0));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p3",50, -50));

    //LINHAS
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("l1",10,10,50,100));
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("l2",0,-230,240,0));

    //POLIGONOS
    Minha_Face* triangulo = new Minha_Face("f1");
    triangulo->addLinha(450, -210, 550, -150);
    triangulo->addLinha(550, -150, 500, -100);
    triangulo->addLinha(500, -100, 450, -210);
    ui->Mundo->displayFile.insertInicio(triangulo);

    Minha_Face* estrela = new Minha_Face("f2");
    estrela->addLinha(-200, 20, -271, -197);
    estrela->addLinha(-271, -197, -86, -63);
    estrela->addLinha(-86, -63, -314, -63);
    estrela->addLinha(-314, -63, -129, -197);
    estrela->addLinha(-129, -197, -200, 20);
    ui->Mundo->displayFile.insertInicio(estrela);

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
    ui->Mundo->getWindow().pan(0, -20.0);
    //qDebug() << "Centro da Câmera movido para:" << ui->Mundo->getWindow().getCentro();
    ui->Mundo->update();
}

void MainWindow::on_btnPanBaixo_clicked()
{
    ui->Mundo->getWindow().pan(0, 20.0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanEsquerda_clicked()
{
    ui->Mundo->getWindow().pan(-20.0, 0);
    ui->Mundo->update();
}

void MainWindow::on_btnPanDireita_clicked()
{
    ui->Mundo->getWindow().pan(20.0, 0);
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
