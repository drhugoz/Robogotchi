#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <model.h>

class Transform
{
public:
    Transform();
    vector<vector<point>> RotatePoints(vector<vector<point>>&, const vector<double>&,  point c = point(0, HEIGHT / 2 * SCALE, 0));
    point RotatePoint(const point&, const vector<double>&,  point c = point(0, HEIGHT / 2 * SCALE, 0));

private:
};

#endif // TRANSFORM_H
