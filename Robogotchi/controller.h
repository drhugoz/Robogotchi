#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "widget.h"
#include "model.h"
#include "painter.h"
#include "scene.h"

class controller : QGraphicsScene
{
    Q_OBJECT
public:
    controller();
    ~controller();

    void startModel();

    Widget* w;

private slots:
    void rotateModel(vector<double>);
    void partMove(int, bool);
private:
    Scene* my_scene;
    Model* my_model;
    Painter* my_painter;
    Transform* my_transform;
    vector<double> changeByPart(int, point&, bool);
};

#endif // CONTROLLER_H
