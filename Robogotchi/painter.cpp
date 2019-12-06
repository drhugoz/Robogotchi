#include "painter.h"
#include <QDebug>
#include <math.h>

#define W 800
#define H 600
#define MAXZ 1000

Painter::Painter()
{

}

void Painter::setScene(Scene *input) {
    curScene = input;
}

vector<vector<double>> Painter::clearPIX(int We, int Hi, int maxVal) {
    vector<vector<double>> pix;
    pix.resize(We);
    for (int i = 0; i < We; ++i) {
        pix[i].resize(Hi);
        for (int j = 0; j < Hi; ++j) {
            pix[i][j] = maxVal;
        }
    }

    return pix;
}

QImage Painter::createZ(vector<vector<point>> input) {
    QImage img = QImage(W, H, QImage::Format_RGB32);
    vector<vector<double>> pix = clearPIX(W, H, MAXZ);
    int ymax = 0, ymin = 0, ysc = 0, e1 = 0, e = 0;

    for (auto part: input) {
        int N = static_cast<int>(part.size());
        for (int i = 0; i < N; ++i) {
            part[i].x += W/2;
            part[i].z += 500;
        }
        ymax = ymin = part[0].y;
        if (ymax < part[1].y)
            ymax = part[1].y;
        else if (ymin > part[1].y)
            ymin = part[1].y;

        if (ymax < part[2].y)
            ymax = part[2].y;
        else if (ymin > part[2].y)
            ymin = part[2].y;
        ymin = ( ymin < 0 ) ? 0 : ymin;
        ymax = ( ymax < H ) ? ymax : H;
        int ne;
        int x1 = 0, x2 = 0, xsc1 = 0, xsc2 = 0;
        double z1 = 0, z2 = 0, tc = 0, z = 0;
        for (ysc = ymin; ysc <= ymax; ysc++) {
            ne = 0;
            for (int e = 0; e < 3; e++) {
                e1 = e + 1;
                if (e1 == 3)
                    e1 = 0;
                if (part[size_t(e)].y <= part[size_t(e1)].y) {
                    if (part[size_t(e1)].y <= ysc || ysc <= part[size_t(e)].y ) continue;
                } else if (part[size_t(e)].y >= part[size_t(e1)].y ) {
                    if (part[size_t(e1)].y >= ysc || ysc >= part[size_t(e)].y ) continue;
                } else continue;
                tc = double(part[e].y - ysc) / (part[e].y - part[e1].y);
                if (ne) {
                    x2 = part[e].x + int (tc * (part[e1].x - part[e].x));
                    z2 = part[e].z + tc * (part[e1].z - part[e].z );
                } else {
                    x1 = part[e].x + int(tc * (part[e1].x - part[e].x));
                    z1 = part[e].z + tc * (part[e1].z - part[e].z);
                    ne = 1;
                }
            }
            if (x2 < x1) {
                e = x1;
                x1 = x2;
                x2 = e;
                tc = z1;
                z1 = z2;
                z2 = tc;
            }
            if (x1 <= 0 || x2 >= W) continue;
            xsc1 = ( x1 < 0 ) ? 0 : x1;
            xsc2 = ( x2 < W ) ? x2 : W;
            for (int xsc = xsc1; xsc <= xsc2; xsc++) {
                tc = double(x1 - xsc) / (x1 - x2);
                z = z1 + tc * ( z2 - z1 );
                if (z < pix[xsc][ysc])
                    pix[xsc][ysc] = z;
            }
        }
    }

    double minZ = 1000, maxZ = -1000;
    img.fill(QColor("white"));
    for (int x = 0; x < W; ++x) {
        for (int y = 0; y < H; ++y) {
            if (pix[x][y] > maxZ && pix[x][y] != MAXZ)
                maxZ = pix[x][y];
            if (pix[x][y] < minZ)
                minZ = pix[x][y];
            int color = pix[x][y] / MAXZ * 255;
            img.setPixelColor(x, H - 1 - y, QColor(color, color, color));
        }
    }

    //qDebug() << minZ << maxZ;

    return img;
}

void Painter::draw(vector<vector<point>> input) {
    QImage result = createZ(input);
    curScene->clear();
    curScene->addPixmap(QPixmap::fromImage(result));
}

void Painter::drawOld(vector<vector<point>> input) {
    curScene->clear();
    for (auto part: input) {
        curScene->addLine(part[0].x + 400, -part[0].y, part[1].x + 400, -part[1].y);
        curScene->addLine(part[0].x + 400, -part[0].y, part[2].x + 400, -part[2].y);
        curScene->addLine(part[1].x + 400, -part[1].y, part[2].x + 400, -part[2].y);
    }
}
