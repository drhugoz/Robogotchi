#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <model.h>
#include <transform.h>
#include <scene.h>
#include <mathvector.h>

class Painter
{
public:
    Painter();

    void setScene(Scene*);

    void draw(const vector<vector<point>>& result, const light&, const vector<QColor>&) const;
    vector<vector<double>> clearPIX(const int& We, const int& Hi, const int& maxVal) const;
    vector<vector<QColor>> clearCOL(const int& We, const int& Hi, const QColor& col) const;

private:
    Scene* curScene;
    QImage createZ(const vector<vector<point>>& input, const light& _light, const vector<QColor>& colors, const vector<vector<bool>>& shadows = vector<vector<bool>>{}) const;
    QColor createColor(vector<point>, QColor, light) const;
    vector<vector<bool>> calculateShadow(const vector<vector<point>>& input, const light& _light) const;
    QImage drawLight(QImage&, const light&) const;
};

#endif // PAINTER_H
