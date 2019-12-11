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

    void startModel() const;

    Widget* w;

private slots:
    void rotateModel(const vector<double>&) const;
    void partMove(const int&, const bool&) const;
    void jumpMove(const vector<double>&) const;
private:
    Scene* my_scene;
    Model* my_model;
    Painter* my_painter;
    Transform* my_transform;
    vector<double> changeByPart(const int&, point&, const bool&) const;
};

#endif // CONTROLLER_H
