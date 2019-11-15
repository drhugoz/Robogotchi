#ifndef MODEL_H
#define MODEL_H

#include <vector>
using std::vector;

#define HEIGHT 50

struct point {
    float x;
    float y;
    float z;
    point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

class Model {
public:
    Model();
    ~Model() = default;

private:
    void inizialize_points();

    point _head_center = point(0, 0, HEIGHT);
    vector<int> _head_sizes = {10, 10, 10};

    point _mouth_center = point(6, 0, HEIGHT - 3);
    vector<int> _mouth_sizes = {2, 6, 2};

    point _ear_center_left = point(0, -6, HEIGHT);
    point _ear_center_right = point(0, 6, HEIGHT);
    vector<int> _ear_sizes = {4, 2, 4};

    point _eye_center_left = point(6, -2, HEIGHT + 2);
    point _eye_center_right = point(6, 2, HEIGHT + 2);
    vector<int> _eye_sizes = {2, 2, 2};

    point _horn_center_left = point(0, -2, HEIGHT + 6);
    point _horn_center_right = point(0, 2, HEIGHT + 6);
    vector<int> _horn_sizes = {2, 2, 2};

    vector<point> _head;
    vector<point> _mouth;
    vector<point> _ear_left;
    vector<point> _ear_right;
    vector<point> _eye_left;
    vector<point> _eye_right;
    vector<point> _horn_left;
    vector<point> _horn_right;

};

#endif // MODEL_H
