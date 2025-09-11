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
    void on_btnTransladar_clicked();
    void on_btnEscalar_clicked();
    void on_btnRotacionar_clicked();

private:
    Ui::MainWindow *ui;
    void preencherListaObjetos();
};
#endif // MAINWINDOW_H
