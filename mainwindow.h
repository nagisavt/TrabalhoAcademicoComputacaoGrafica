#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
=======
#include <QString>
#include <vector>
>>>>>>> de9c65f (Implementacao de transformacoes geometricas)

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

<<<<<<< HEAD
private:
    Ui::MainWindow *ui;
=======
private slots:
    void on_btnTransladar_clicked();
    void on_btnEscalar_clicked();
    void on_btnRotacionar_clicked();

private:
    Ui::MainWindow *ui;
    void preencherListaObjetos();
>>>>>>> de9c65f (Implementacao de transformacoes geometricas)
};
#endif // MAINWINDOW_H
