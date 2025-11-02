#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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

    void on_btnGirarHorario_clicked();
    void on_btnGirarAntiHorario_clicked();

    void on_btnProjecaoXY_clicked();
    void on_btnProjecaoZX_clicked();
    void on_btnProjecaoZY_clicked();

private:
    Ui::MainWindow *ui;
    void preencherListaObjetos();
};
#endif // MAINWINDOW_H
