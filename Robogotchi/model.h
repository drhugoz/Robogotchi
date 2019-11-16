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
    Model() {
        _initialize_model();
    }
    ~Model() = default;

    vector<vector<point>> GiveMePoints() const;

private:
    void _initialize_model();
    vector<point> _initialize_part(point, vector<int>);

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

    /*vector<point> _head = all_coords_comb(_head_center.x + _head_sizes[0] / 2,
                                                _head_center.y + _head_sizes[1] / 2,
                                                _head_center.z + _head_sizes[2] / 2,
                                                _head_center.z - _head_sizes[2] / 2);
    vector<point> _mouth = all_coords_comb(_mouth_center.x + _mouth_sizes[0] / 2,
                                                  _mouth_center.y + _mouth_sizes[1] / 2,
                                                  _mouth_center.z + _mouth_sizes[2] / 2,
                                                  _mouth_center.z - _mouth_sizes[2] / 2);
    vector<point> _ear_left = all_coords_comb(_ear_center_left.x + _ear_sizes[0] / 2,
                                                  _ear_center_left.y + _ear_sizes[1] / 2,
                                                  _ear_center_left.z + _ear_sizes[2] / 2,
                                                  _ear_center_left.z - _ear_sizes[2] / 2);
    vector<point> _ear_right = all_coords_comb(_ear_center_right.x + _ear_sizes[0] / 2,
                                                  _ear_center_right.y + _ear_sizes[1] / 2,
                                                  _ear_center_right.z + _ear_sizes[2] / 2,
                                                  _ear_center_right.z - _ear_sizes[2] / 2);
    vector<point> _eye_left = all_coords_comb(_eye_center_left.x + _eye_sizes[0] / 2,
                                                  _eye_center_left.y + _eye_sizes[1] / 2,
                                                  _eye_center_left.z + _eye_sizes[2] / 2,
                                                  _eye_center_left.z - _eye_sizes[2] / 2);
    vector<point> _eye_right = all_coords_comb(_eye_center_right.x + _eye_sizes[0] / 2,
                                                  _eye_center_right.y + _eye_sizes[1] / 2,
                                                  _eye_center_right.z + _eye_sizes[2] / 2,
                                                  _eye_center_right.z - _eye_sizes[2] / 2);
    vector<point> _horn_left = all_coords_comb(_horn_center_left.x + _horn_sizes[0] / 2,
                                                  _horn_center_left.y + _horn_sizes[1] / 2,
                                                  _horn_center_left.z + _horn_sizes[2] / 2,
                                                  _horn_center_left.z - _horn_sizes[2] / 2);
    vector<point> _horn_right = all_coords_comb(_horn_center_right.x + _horn_sizes[0] / 2,
                                                  _horn_center_right.y + _horn_sizes[1] / 2,
                                                  _horn_center_right.z + _horn_sizes[2] / 2,
                                                  _horn_center_right.z - _horn_sizes[2] / 2);*/

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
