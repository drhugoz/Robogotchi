#include "scene.h"
#include <QDebug>

Scene::Scene() : shadow(0), curLight(0), curLightColor(0), intens(1), x_a(0), y_a(3.1), z_a(0), leftHand(false), rightHand(false), leftLeg(false), rightLeg(false),
    head(false)
{
    point view = point(0, HEIGHT * SCALE, 0);
    Transform trans;
    for (int i = 0; i < int(_light_param.size()); ++i) {
        _light_places.push_back(trans.RotatePoint(view, _light_param[i]));
    }
}

light Scene::GiveLight() const {
    return light(_light_places[curLight], intens, _light_colors[curLightColor], _light_param[curLight], shadow);
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
    if (event->key() == Qt::Key_L) {
        curLight++;
        if (curLight == 4) curLight = 0;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_Equal) {
        if (intens < 1.2) {
            intens += 0.1;
            emit rotateModel(vector<double>{x_a, y_a, z_a});
        }
    }
    if (event->key() == Qt::Key_Minus) {
        if (intens > 0) {
            intens -= 0.1;
            emit rotateModel(vector<double>{x_a, y_a, z_a});
        }
    }
    if (event->key() == Qt::Key_0) {
        curLightColor = 0;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_1) {
        curLightColor = 1;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_2) {
        curLightColor = 2;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_3) {
        curLightColor = 3;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_4) {
        curLightColor = 4;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_5) {
        curLightColor = 5;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_6) {
        curLightColor = 6;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_7) {
        curLightColor = 7;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_8) {
        curLightColor = 8;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_9) {
        curLightColor = 9;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
    if (event->key() == Qt::Key_T) {
        shadow = !shadow;
        emit rotateModel(vector<double>{x_a, y_a, z_a});
    }
}

