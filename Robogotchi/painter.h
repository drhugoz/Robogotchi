#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <model.h>

class Painter
{
public:
    Painter();

    void setScene(QGraphicsScene*);

    void draw(vector<vector<point>>);

private:
    QGraphicsScene* curScene;
};

#endif // PAINTER_H
