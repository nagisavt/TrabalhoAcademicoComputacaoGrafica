#ifndef MEU_FRAME_H
#define MEU_FRAME_H


#include "display_file.h"
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

private:
    void desenharDisplayFile(QPainter& painter);
public:
    DisplayFile displayFile;
    explicit Meu_frame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

public slots:

    void desenhar();
};

#endif // MEU_FRAME_H










