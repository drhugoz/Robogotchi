#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <model.h>

class Transform
{
public:
    Transform();
    vector<vector<point>> RotatePoints(const vector<vector<point>>&, const vector<double>&,  const point& c = point(0, HEIGHT / 2 * SCALE, 0)) const;
    point RotatePoint(const point&, const vector<double>&,  const point& c = point(0, HEIGHT / 2 * SCALE, 0)) const;
    vector<vector<point>> jump(const vector<vector<point>>&, const int&) const;

private:
};

#endif // TRANSFORM_H
