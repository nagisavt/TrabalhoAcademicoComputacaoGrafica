#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meu_frame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //PONTOS
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p1",50, 50));
    ui->Mundo->displayFile.insertInicio(new Meu_Ponto("p2", 0, 0));

    //LINHAS
    ui->Mundo->displayFile.insertInicio(new Minha_Linha("l1",10,10,50,100));

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

MainWindow::~MainWindow()
{
    delete ui;
}
