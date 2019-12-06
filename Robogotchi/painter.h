#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <model.h>
#include <transform.h>
#include <scene.h>

class Painter
{
public:
    Painter();

    void setScene(Scene*);

    void drawOld(vector<vector<point>>);
    void draw(vector<vector<point>> result);


private:
    Scene* curScene;
    vector<vector<double>> clearPIX(int We, int Hi, int maxVal);
    QImage createZ(vector<vector<point>>);
};

#endif // PAINTER_H
