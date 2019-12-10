#include "controller.h"
#include <QDebug>

controller::controller() {
    my_scene = new Scene;
    w = new Widget;
    my_painter = new Painter;
    my_model = new Model;
    my_transform = new Transform;
    w->setScene(my_scene);
    my_painter->setScene(my_scene);
    startModel();

    QObject::connect(my_scene, SIGNAL(rotateModel(vector<double>)), this, SLOT(rotateModel(vector<double>)));
    QObject::connect(my_scene, SIGNAL(partMove(int, bool)), this, SLOT(partMove(int, bool)));
}

controller::~controller()
{
    delete my_transform;
    delete my_model;
    delete my_painter;
    delete w;
    delete my_scene;
}

void controller::startModel() {
    vector<double> param = {0, 3.1, 0};
    vector<vector<point>> points = my_model->GiveMePoints3();
    vector<QColor> colors = my_model->GiveMeColors();
    my_scene->SetModel(points);
    my_painter->draw(my_transform->RotatePoints(points, param), my_scene->GiveLight(), colors);
}

void controller::rotateModel(vector<double> param) {
    vector<vector<point>> points = my_scene->GiveModel();
    vector<QColor> colors = my_model->GiveMeColors();
    my_scene->SetModel(points);
    my_painter->draw(my_transform->RotatePoints(points, param), my_scene->GiveLight(), colors);
}

void controller::partMove(int partNum, bool s) {
    vector<vector<point>> model = my_scene->GiveModel();
    point center = my_model->GiveMeCenters()[partNum];
    vector<double> param = changeByPart(partNum, center, s);
    for (int i = 0; i < 12; ++i) {
        vector<point> newPart;
        vector<point> part = model[partNum * 12 + i];
        for (auto p : part)
            newPart.push_back(my_transform->RotatePoint(p, param, center));
        model[partNum * 12 + i] = newPart;
    }
    my_scene->SetModel(model);
    vector<QColor> colors = my_model->GiveMeColors();
    if (partNum == 0) {
        for (int i = 1; i <= 7; ++i) {
            partMove(i, s);
        }
        my_painter->draw(my_transform->RotatePoints(model, my_scene->GiveAngles()), my_scene->GiveLight(), colors);
    } else if (partNum >= 8) {
        my_painter->draw(my_transform->RotatePoints(model, my_scene->GiveAngles()), my_scene->GiveLight(), colors);
    }
}

vector<double> controller::changeByPart(int partNum, point& center, bool s) {
    if (partNum == L_ARM || partNum == R_ARM) { // hands
        center.y = center.y + 3 * SCALE;
        if (!s)
            return vector<double>{2, 0, 0};
        return vector<double>{-2, 0, 0};
    } else if (partNum == L_LEG || partNum == R_LEG) { // hands
        center.y = center.y + 7 * SCALE;
        if (!s)
            return vector<double>{1.9, 0, 0};
        return vector<double>{-1.9, 0, 0};
    } else {//if (partNum >= HEAD && partNum <= 7) {
        center = my_model->GiveMeCenters()[0];
        if (!s)
            return vector<double>{0, 0.1, 0};
        return vector<double>{0, 0.1, 0};
    }
}

