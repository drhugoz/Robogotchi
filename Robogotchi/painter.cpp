#include "painter.h"
#include <QDebug>

Painter::Painter()
{

}

void Painter::setScene(QGraphicsScene *input) {
    curScene = input;
}

void Painter::draw(vector<vector<point>> input) {
    for (auto v : input) {
        qDebug() << "\nNew";
        for (int i = 0; i < v.size(); ++i) {
            qDebug() << v[i].x << " " << v[i].y <<  " " << v[i].z << "\n";
        }
        //qDebug() << v[3].y << v[3].z << v[4].y << v[4].z;
        curScene->addLine(v[0].y, -v[0].z, v[1].y, -v[1].z);
        curScene->addLine(v[1].y, -v[1].z, v[2].y, -v[2].z);
        curScene->addLine(v[2].y, -v[2].z, v[3].y, -v[3].z);
        curScene->addLine(v[3].y, -v[3].z, v[0].y, -v[0].z);

        curScene->addLine(v[4].y, -v[4].z, v[5].y, -v[5].z);
        curScene->addLine(v[5].y, -v[5].z, v[6].y, -v[6].z);
        curScene->addLine(v[6].y, -v[6].z, v[7].y, -v[7].z);
        curScene->addLine(v[7].y, -v[7].z, v[4].y, -v[4].z);

        curScene->addLine(v[0].y, -v[0].z, v[4].y, -v[4].z);
        curScene->addLine(v[1].y, -v[1].z, v[5].y, -v[5].z);
        curScene->addLine(v[2].y, -v[2].z, v[6].y, -v[6].z);
        curScene->addLine(v[3].y, -v[3].z, v[7].y, -v[7].z);
    }
}
