#include "scene.h"

Scene::Scene() : x_a(0), y_a(3.3), z_a(0), leftHand(false), rightHand(false), leftLeg(false), rightLeg(false),
    head(false)
{

}

void Scene::SetModel(vector<vector<point>> input) {
    model = input;
}

vector<vector<point>> Scene::GiveModel() {
    return model;
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        y_a -= 0.1;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_Right) {
        y_a += 0.1;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_Up) {
        x_a -= 0.1;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_Down) {
        x_a += 0.1;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_Q) {
        emit partMove(L_ARM, leftHand);
        leftHand = !leftHand;
    }
    if (event->key() == Qt::Key_W) {
        emit partMove(R_ARM, rightHand);
        rightHand = !rightHand;
    }
    if (event->key() == Qt::Key_A) {
        emit partMove(L_LEG, leftLeg);
        leftLeg = !leftLeg;
    }
    if (event->key() == Qt::Key_S) {
        emit partMove(R_LEG, rightLeg);
        rightLeg = !rightLeg;
    }
    if (event->key() == Qt::Key_H) {
        emit partMove(HEAD, head);
        head = !head;
    }

}
