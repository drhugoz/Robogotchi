#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include "model.h"

using std::vector;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    ~Scene() {}

    void SetModel(vector<vector<point>>);
    vector<vector<point>> GiveModel();
    vector<double> GiveAngles() {return vector<double>{x_a, y_a, z_a};}

signals:
    void rotateModel(vector<double>);
    void partMove(int, bool);

private:
    vector<vector<point>> model;
    double x_a, y_a, z_a;
    void keyPressEvent(QKeyEvent *event);

    bool leftHand;
    bool rightHand;
    bool leftLeg;
    bool rightLeg;
    bool head;
};

#endif // SCENE_H
