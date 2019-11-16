#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include "widget.h"
#include "model.h"
#include "painter.h"

class controller
{
public:
    controller();
    ~controller();

    Widget* w;
private:
    QGraphicsScene* my_scene;
    Model* my_model;
    Painter* my_painter;
};

#endif // CONTROLLER_H
