#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "read_obj.h"
#include <QMainWindow>
#include <Qstring>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //
    void on_btnTransladar_clicked();
    void on_btnEscalar_clicked();

    void on_btnRotacionarX_clicked();
    void on_btnRotacionarY_clicked();
    void on_btnRotacionarZ_clicked();

    void on_btnPanCima_clicked();
    void on_btnPanBaixo_clicked();
    void on_btnPanEsquerda_clicked();
    void on_btnPanDireita_clicked();

    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();

    void on_btnHorX_clicked();
    void on_btnAntiX_clicked();
    void on_btnHorY_clicked();
    void on_btnAntiY_clicked();
    void on_btnHorZ_clicked();
    void on_btnAntiZ_clicked();


    void on_btnProjecaoXY_clicked();
    void on_btnProjecaoXZ_clicked();
    void on_btnProjecaoYZ_clicked();
    void on_btnProjecaoPerspectiva_clicked();

private:
    Meu_Objeto* getObjetoSelecionado();
    Ui::MainWindow *ui;
    void preencherListaObjetos();
    read_obj m_objloader;
};
#endif // MAINWINDOW_H
