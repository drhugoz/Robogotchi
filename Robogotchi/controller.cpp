#include "controller.h"

controller::controller()
{
    my_scene = new QGraphicsScene;
    w = new Widget;
    my_painter = new Painter;
    my_model = new Model;
    w->setScene(my_scene);
    my_painter->setScene(my_scene);
    my_painter->draw(my_model->GiveMePoints());
}

controller::~controller()
{
    delete my_model;
    delete my_painter;
    delete w;
    delete my_scene;
}
