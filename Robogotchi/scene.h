#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include "model.h"
#include "transform.h"

using std::vector;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    ~Scene() {}

    void SetModel(const vector<vector<point>>&);
    vector<vector<point>> GiveModel() const;
    vector<double> GiveAngles() const {return vector<double>{x_a, y_a, z_a};}
    light GiveLight() const;

signals:
    void rotateModel(vector<double>);
    void partMove(int, bool);
    void jumpMove(vector<double>);

private:
    bool shadow;
    vector<point> _light_places;
    vector<vector<double>> _light_param = {{0.2, 0.6, 0},
                                                 {0.2, -0.6, 0},
                                                 {-0.2, 0.6, 0},
                                                 {-0.2, -0.6, 0}};
    int curLight;

    vector<QColor> _light_colors = {QColor(0, 0, 0),
                                       QColor(128, 0, 0),
                                       QColor(128, 32, 0),
                                       QColor(128, 64, 32),
                                       QColor(0, 128, 0),
                                       QColor(32, 128, 0),
                                       QColor(64, 128, 32),
                                       QColor(0, 0, 128),
                                       QColor(0, 32, 128),
                                       QColor(32, 64, 128),
                                   };
    int curLightColor;

    double intens;
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
