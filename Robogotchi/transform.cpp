#include "transform.h"
#include <math.h>

Transform::Transform()
{

}

vector<vector<point>> Transform::RotatePoints(const vector<vector<point>>& input, const vector<double>& param, const point& c) const {
    vector<vector<point>> result;
    for (auto part: input) {
        vector<point> partResult;
        for (auto p : part) {
            point one = RotatePoint(p, param, c);
            partResult.push_back(one);
        }
        result.push_back(partResult);
    }
    return result;
}

point Transform::RotatePoint(const point& input, const vector<double>& param, const point& c) const {
    point newP = point(input.x, input.y, input.z);
    double y_copy = input.y;
    newP.y = c.y + (newP.y - c.y) * cos(param[0]) + (newP.z - c.z) * sin(param[0]);
    newP.z = c.z + (c.y - y_copy) * sin(param[0]) + (newP.z - c.z) * cos(param[0]);

    double x_copy = newP.x;
    newP.x = c.x + (newP.x - c.x) * cos(param[1]) + (newP.z - c.z) * sin(param[1]);
    newP.z = c.z + (c.x - x_copy) * sin(param[1]) + (newP.z - c.z) * cos(param[1]);

    x_copy = newP.x;
    newP.x = c.x + (newP.x - c.x) * cos(param[2]) - (newP.y - c.y) * sin(param[2]);
    newP.y = c.y + (x_copy - c.x) * sin(param[2]) + (newP.y - c.y) * cos(param[2]);

    return newP;
}

vector<vector<point>> Transform::jump(const vector<vector<point>>& input, const int& d) const {
    vector<vector<point>> result;
    for (auto part: input) {
        vector<point> partResult;
        for (auto p : part) {
            point one = p;
            one.y += d;
            partResult.push_back(one);
        }
        result.push_back(partResult);
    }
    return result;
}
