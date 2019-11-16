#include "model.h"

#define s 15

vector<vector<point>> Model::GiveMePoints() const {
    vector<vector<point>> result;
    result.push_back(_head);
    result.push_back(_mouth);
    result.push_back(_eye_left);
    result.push_back(_eye_right);
    result.push_back(_ear_left);
    result.push_back(_ear_right);
    result.push_back(_horn_left);
    result.push_back(_horn_right);

    return result;
}

vector<point> Model::_initialize_part(point center, vector<int> sizes) {
    vector<point> result;
    result.push_back(point(s*(center.x + sizes[0]/2), s*(center.y + sizes[1]/2), s*(center.z + sizes[2]/2)));
    result.push_back(point(s*(center.x + sizes[0]/2), s*(center.y - sizes[1]/2), s*(center.z + sizes[2]/2)));
    result.push_back(point(s*(center.x - sizes[0]/2), s*(center.y - sizes[1]/2), s*(center.z + sizes[2]/2)));
    result.push_back(point(s*(center.x - sizes[0]/2), s*(center.y + sizes[1]/2), s*(center.z + sizes[2]/2)));
    result.push_back(point(s*(center.x + sizes[0]/2), s*(center.y + sizes[1]/2), s*(center.z - sizes[2]/2)));
    result.push_back(point(s*(center.x + sizes[0]/2), s*(center.y - sizes[1]/2), s*(center.z - sizes[2]/2)));
    result.push_back(point(s*(center.x - sizes[0]/2), s*(center.y - sizes[1]/2), s*(center.z - sizes[2]/2)));
    result.push_back(point(s*(center.x - sizes[0]/2), s*(center.y + sizes[1]/2), s*(center.z - sizes[2]/2)));

    return result;
}

void Model::_initialize_model() {
    _head = _initialize_part(_head_center, _head_sizes);
    _mouth = _initialize_part(_mouth_center, _mouth_sizes);
    _eye_left = _initialize_part(_eye_center_left, _eye_sizes);
    _eye_right = _initialize_part(_eye_center_right, _eye_sizes);
    _ear_left = _initialize_part(_ear_center_left, _ear_sizes);
    _ear_right = _initialize_part(_ear_center_right, _ear_sizes);
    _horn_left = _initialize_part(_horn_center_left, _horn_sizes);
    _horn_right = _initialize_part(_horn_center_right, _horn_sizes);
}
