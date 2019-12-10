#ifndef MODEL_H
#define MODEL_H

#include <QColor>
#include <vector>
using std::vector;

#define HEIGHT 50
#define SCALE 9

#define W 800
#define H 600
#define MAXZ 1000

#define HEAD 0
#define MOUTH 1
#define L_EYE 2
#define R_EYE 3
#define L_EAR 4
#define R_EAR 5
#define L_HORN 6
#define R_HORN 7
#define BODY 8
#define L_ARM 9
#define R_ARM 10
#define L_LEG 11
#define R_LEG 12

struct point {
    double x;
    double y;
    double z;
    point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    point operator*(int input) const {
        point newP = point(x, y, z);
        newP.x *= input;
        newP.y *= input;
        newP.z *= input;
        return newP;
    }
};

struct light {
    point place;
    double intens;
    QColor color;
    vector<double> param;
    bool shadow;
    light(point _p, double _int, QColor col, vector<double> _param, bool _sh) : place(_p), intens(_int), color(col), param(_param), shadow(_sh) {}
};

class Model {
public:
    Model() {
        _initialize_model();
    }
    ~Model() = default;

    vector<vector<point>> GiveMePoints() const;
    vector<vector<point>> GiveMePoints3() const;
    vector<point> GiveMeCenters() const;
    vector<QColor> GiveMeColors() const;

private:
    void _initialize_model();
    vector<point> _initialize_part(point, vector<int>);
    vector<vector<point>> triangles;

    vector<QColor> colors = {QColor(200, 200, 150), //head
                                QColor(100, 70, 80), // mouth
                                QColor(240, 100, 60), //eye
                                QColor(240, 100, 60),
                                QColor(250, 190, 200), //ear
                                QColor(250, 190, 200),
                                QColor(255, 255, 0), //horn
                                QColor(255, 255, 0),
                                QColor(133, 196, 38), //body
                                QColor(200, 200, 150), //arm
                                QColor(200, 200, 150),
                                QColor(200, 200, 150), //leg
                                QColor(200, 200, 150),
                        QColor(255, 0, 0)};

    point _head_center = point(0, HEIGHT, 0);
    vector<int> _head_sizes = {10, 10, 10};

    point _mouth_center = point(0, HEIGHT - 2, 6);
    vector<int> _mouth_sizes = {6, 2, 2};

    point _ear_center_left = point(-6, HEIGHT, 0);
    point _ear_center_right = point(6, HEIGHT, 0);
    vector<int> _ear_sizes = {2, 4, 4};

    point _eye_center_left = point(-2, HEIGHT + 2, 6);
    point _eye_center_right = point(2, HEIGHT + 2, 6);
    vector<int> _eye_sizes = {2, 2, 2};

    point _horn_center_left = point(-2, HEIGHT + 6, 0);
    point _horn_center_right = point(2, HEIGHT + 6, 0);
    vector<int> _horn_sizes = {2, 2, 2};

    point _body_center = point(0, HEIGHT - 15, 0);
    vector<int> _body_sizes = {16, 20, 6};

    point _arm_center_left = point(-10, HEIGHT - 12, 0);
    point _arm_center_right = point(10, HEIGHT - 12, 0);
    vector<int> _arm_sizes = {4, 14, 6};

    point _leg_center_left = point(-4, HEIGHT - 32, 0);
    point _leg_center_right = point(4, HEIGHT - 32, 0);
    vector<int> _leg_sizes = {6, 14, 6};

    vector<point> _head;
    vector<point> _mouth;
    vector<point> _ear_left;
    vector<point> _ear_right;
    vector<point> _eye_left;
    vector<point> _eye_right;
    vector<point> _horn_left;
    vector<point> _horn_right;

    vector<point> _arm_left;
    vector<point> _arm_right;
    vector<point> _leg_left;
    vector<point> _leg_right;
    vector<point> _body;

};

#endif // MODEL_H
