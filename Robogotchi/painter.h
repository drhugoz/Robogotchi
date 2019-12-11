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

    void drawOld(vector<vector<point>>);
    void draw(vector<vector<point>> result, light, vector<QColor>);
    vector<vector<double>> clearPIX(int We, int Hi, int maxVal);
    vector<vector<QColor>> clearCOL(int We, int Hi, QColor col);

private:
    Scene* curScene;
    QImage createZ(vector<vector<point>>, light, vector<QColor>, vector<vector<bool>> shad = vector<vector<bool>>{});
    QColor createColor(vector<point>, QColor, light);
    QColor createColorNew(MathVector n, point p, QColor input, light _light);
    vector<vector<bool>> calculateShadow(vector<vector<point>> input, light);
    vector<vector<double>> calculateShadowUpgrade(vector<vector<point>> input, light); //bad
    QImage drawLight(QImage, light);
};

#endif // PAINTER_H
