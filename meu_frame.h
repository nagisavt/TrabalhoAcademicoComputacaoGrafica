#ifndef MEU_FRAME_H
#define MEU_FRAME_H

#include "display_file.h"
#include "window.h"
#include <QFrame>
#include <QWidget>
#include <QPaintEvent>
#include <QRect>
#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QtMath>

class Meu_frame : public QFrame
{
    Q_OBJECT

public:
    enum class TipoProjecao{
        XY,
        XZ,
        YZ,
        PERSPECTIVA

    };
private:
    void desenharDisplayFile(QPainter& painter);
    Window window;
    TipoProjecao m_projecao = TipoProjecao::PERSPECTIVA;
    double d = 500.0;
public:
    DisplayFile displayFile;
    explicit Meu_frame(QWidget *parent = nullptr);
    Window& getWindow() { return window; }
    void paintEvent(QPaintEvent *event) override;

    void setProjecao(TipoProjecao proj){
        m_projecao = proj;
        update();
    }

public slots:

    void desenhar();
};

#endif // MEU_FRAME_H










