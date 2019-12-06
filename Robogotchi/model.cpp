#include "model.h"

vector<vector<point>> Model::GiveMePoints3() const {
     vector<vector<point>> squares = GiveMePoints();
      vector<vector<point>> triangles;
     for (auto part: squares) {
        vector<point> _triangle;
        _triangle.push_back(part[0]);
        _triangle.push_back(part[1]);
        _triangle.push_back(part[2]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[0]);
        _triangle.push_back(part[2]);
        _triangle.push_back(part[3]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[0]);
        _triangle.push_back(part[3]);
        _triangle.push_back(part[4]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[3]);
        _triangle.push_back(part[4]);
        _triangle.push_back(part[7]);
        triangles.push_back(_triangle);
        _triangle.clear();


        _triangle.push_back(part[4]);
        _triangle.push_back(part[5]);
        _triangle.push_back(part[6]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[4]);
        _triangle.push_back(part[6]);
        _triangle.push_back(part[7]);
        triangles.push_back(_triangle);
        _triangle.clear();


        _triangle.push_back(part[1]);
        _triangle.push_back(part[6]);
        _triangle.push_back(part[2]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[1]);
        _triangle.push_back(part[6]);
        _triangle.push_back(part[5]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[0]);
        _triangle.push_back(part[1]);
        _triangle.push_back(part[4]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[1]);
        _triangle.push_back(part[4]);
        _triangle.push_back(part[5]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[2]);
        _triangle.push_back(part[3]);
        _triangle.push_back(part[7]);
        triangles.push_back(_triangle);
        _triangle.clear();

        _triangle.push_back(part[2]);
        _triangle.push_back(part[6]);
        _triangle.push_back(part[7]);
        triangles.push_back(_triangle);
        _triangle.clear();
     }

     return triangles;
}

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
    result.push_back(_body);
    result.push_back(_arm_left);
    result.push_back(_arm_right);
    result.push_back(_leg_left);
    result.push_back(_leg_right);


    return result;
}

vector<point> Model::_initialize_part(point center, vector<int> sizes) {
    vector<point> result;
    result.push_back(point(SCALE*(center.x + sizes[0]/2), SCALE*(center.y + sizes[1]/2), SCALE*(center.z + sizes[2]/2)));
    result.push_back(point(SCALE*(center.x + sizes[0]/2), SCALE*(center.y - sizes[1]/2), SCALE*(center.z + sizes[2]/2)));
    result.push_back(point(SCALE*(center.x - sizes[0]/2), SCALE*(center.y - sizes[1]/2), SCALE*(center.z + sizes[2]/2)));
    result.push_back(point(SCALE*(center.x - sizes[0]/2), SCALE*(center.y + sizes[1]/2), SCALE*(center.z + sizes[2]/2)));
    result.push_back(point(SCALE*(center.x + sizes[0]/2), SCALE*(center.y + sizes[1]/2), SCALE*(center.z - sizes[2]/2)));
    result.push_back(point(SCALE*(center.x + sizes[0]/2), SCALE*(center.y - sizes[1]/2), SCALE*(center.z - sizes[2]/2)));
    result.push_back(point(SCALE*(center.x - sizes[0]/2), SCALE*(center.y - sizes[1]/2), SCALE*(center.z - sizes[2]/2)));
    result.push_back(point(SCALE*(center.x - sizes[0]/2), SCALE*(center.y + sizes[1]/2), SCALE*(center.z - sizes[2]/2)));

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
    _body = _initialize_part(_body_center, _body_sizes);
    _arm_left = _initialize_part(_arm_center_left, _arm_sizes);
    _arm_right = _initialize_part(_arm_center_right, _arm_sizes);
    _leg_left = _initialize_part(_leg_center_left, _leg_sizes);
    _leg_right = _initialize_part(_leg_center_right, _leg_sizes);
}

vector<point> Model::GiveMeCenters() const {
    vector<point> center;
    center.push_back(_head_center*SCALE);
    center.push_back(_mouth_center*SCALE);
    center.push_back(_eye_center_left*SCALE);
    center.push_back(_eye_center_right*SCALE);
    center.push_back(_ear_center_left*SCALE);
    center.push_back(_ear_center_right*SCALE);
    center.push_back(_horn_center_left*SCALE);
    center.push_back(_horn_center_right*SCALE);
    center.push_back(_body_center*SCALE);
    center.push_back(_arm_center_left*SCALE);
    center.push_back(_arm_center_right*SCALE);
    center.push_back(_leg_center_left*SCALE);
    center.push_back(_leg_center_right*SCALE);

    return center;
}

