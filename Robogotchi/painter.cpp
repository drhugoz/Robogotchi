#include "painter.h"
#include <QDebug>
#include <math.h>

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
        pix[i].resize(Hi, maxVal);
    }

    return pix;
}

vector<vector<QColor>> Painter::clearCOL(int We, int Hi, QColor col) {
    vector<vector<QColor>> pix;
    pix.resize(We);
    for (int i = 0; i < We; ++i) {
        pix[i].resize(Hi, col);
    }

    return pix;
}

QImage Painter::createZ(vector<vector<point>> input, light _light, vector<QColor> colors, vector<vector<bool>> shadows) {
    QImage img = QImage(W, H, QImage::Format_RGB32);
    vector<vector<double>> pix = clearPIX(W, H, MAXZ);
    vector<vector<QColor>> col = clearCOL(W, H, MAXZ);

    int ymax = 0, ymin = 0, ysc = 0, e1 = 0, e = 0;
    int a = 0;
    QColor c;
    for (auto part: input) {
        //MathVector n = MathVector(part[1], part[2]) * MathVector(part[1], part[0]);
        if (a % 2 == 0)
            c = createColor(part, colors[a/12], _light);
        a++;
        int N = static_cast<int>(part.size());
        for (int i = 0; i < N; ++i) {
            part[i].x += W/2;
            part[i].y += 30;
            //part[i].z += 400;
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
        double x1 = 0, x2 = 0;
        int xsc1 = 0, xsc2 = 0;
        double z1 = 0, z2 = 0, tc = 0, z = 0;
        ymin = floor(ymin);
        ymax = ceil(ymax);
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
            x1 = floor(x1);
            x2 = ceil(x2);
            if (x1 <= 0 || x2 >= W) continue;
            xsc1 = ( x1 < 0 ) ? 0 : x1;
            xsc2 = ( x2 < W ) ? x2 : W;
            for (double xsc = xsc1; xsc <= xsc2; xsc++) {
                tc = double(x1 - xsc) / (x1 - x2);
                z = z1 + tc * ( z2 - z1 );
                if (z < pix[xsc][ysc]) {
                    pix[xsc][ysc] = z;
                    col[xsc][ysc] = c;
                }
            }
        }
    }
    img.fill(QColor("white"));
    if (_light.shadow) {
        for (int x = 0; x < W; ++x) {
            for (int y = 0; y < H; ++y) {
                QColor color = col[x][y];
                if (pix[x][y] != MAXZ)
                    img.setPixelColor(x, H - 1 - y, color.rgb());
                else if (shadows[x][y]) {
                    color = "black";
                    img.setPixelColor(x, H - 1 - y, color.rgb());
                }
            }
        }
    } else {
        for (int x = 0; x < W; ++x) {
            for (int y = 0; y < H; ++y) {
                if (pix[x][y] != MAXZ)
                    img.setPixelColor(x, H - 1 - y, col[x][y].rgb());
            }
        }
    }

    return img;
}

void Painter::draw(vector<vector<point>> input, light _light, vector<QColor> colors) {
    Transform trans;
    vector<double> paramSh = vector<double>{-_light.param[0], -_light.param[1], -_light.param[2]};
    QImage result;
    if (_light.shadow) {
        vector<vector<bool>> shadows = calculateShadow(trans.RotatePoints(input, paramSh), _light);
        result = createZ(input, _light, colors, shadows);
    } else {
        result = createZ(input, _light, colors);
    }
    result = drawLight(result, _light);
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

QColor Painter::createColorNew(MathVector n, point p, QColor input, light _light) {
    MathVector l = MathVector(p, _light.place);
    MathVector h = MathVector(p, point(0, HEIGHT * SCALE, 0));

    int r, g, b;
    input.getRgb(&r, &g, &b);
    n.normalize();
    l.normalize();
    h.normalize();

    double K1, K2;

    K1 = n & l;
    K2 = n & h;

    while (abs(K1) < 100 && abs(K2) < 100)
    {
        K1 *= 10;
        K2 *= 10;
    }

    K1 /= 10;
    K2 /= 10;

    double intens = _light.intens;
    if (r)
        r = (int)(intens * (r + _light.color.red()) + 0.3 * K1 + 0.3 * K2);
    if (g)
        g = (int)(intens * (g + _light.color.green()) + 0.3 * K1 + 0.3 * K2);
    if (b)
        b = (int)(intens * (b + _light.color.blue()) + 0.3 * K1 + 0.3 * K2);

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    return QColor(r, g, b);

}

QColor Painter::createColor(vector<point> part, QColor input, light _light) {
    MathVector n = MathVector(part[1], part[2]) * MathVector(part[1], part[0]);
    MathVector l = MathVector(part[0], _light.place);
    MathVector h = MathVector(part[0], point(0, HEIGHT * SCALE, 0));

    int r, g, b;
    input.getRgb(&r, &g, &b);
    n.normalize();
    l.normalize();
    h.normalize();

    double K1, K2;

    K1 = n & l;
    K2 = n & h;

    while (abs(K1) < 100 && abs(K2) < 100)
    {
        K1 *= 10;
        K2 *= 10;
    }

    K1 /= 10;
    K2 /= 10;

    double intens = _light.intens;
    if (r)
        r = (int)(intens * (r + _light.color.red()) + 0.3 * K1 + 0.3 * K2);
    if (g)
        g = (int)(intens * (g + _light.color.green()) + 0.3 * K1 + 0.3 * K2);
    if (b)
        b = (int)(intens * (b + _light.color.blue()) + 0.3 * K1 + 0.3 * K2);

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    return QColor(r, g, b);

}

vector<vector<bool>> Painter::calculateShadow(vector<vector<point>> input, light _light) {
    vector<vector<double>> pix = clearPIX(W, H, MAXZ);
    int ymax = 0, ymin = 0, ysc = 0, e1 = 0, e = 0;
    for (auto part: input) {
        int N = static_cast<int>(part.size());
        for (int i = 0; i < N; ++i) {
            part[i].x += W/2;
            part[i].y += 30; //* 2;
            //part[i].z += 400;
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
        double x1 = 0, x2 = 0;
        int xsc1 = 0, xsc2 = 0;
        double z1 = 0, z2 = 0, tc = 0, z = 0;
        ymin = floor(ymin);
        ymax = ceil(ymax);
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
            x1 = floor(x1);
            x2 = ceil(x2);
            if (x1 <= 0 || x2 >= W) continue;
            xsc1 = ( x1 < 0 ) ? 0 : x1;
            xsc2 = ( x2 < W ) ? x2 : W;
            for (double xsc = xsc1; xsc <= xsc2; xsc++) {
                tc = double(x1 - xsc) / (x1 - x2);
                z = z1 + tc * ( z2 - z1 );
                if (z < pix[xsc][ysc]) {
                    pix[xsc][ysc] = z;
                }
            }
        }
    }
    vector<vector<bool>> shadBool;
    shadBool.resize(W);
    for (int i = 0; i < W; ++i) {
        shadBool[i].resize(H, 0);
    }
    Transform tr;
    point a(0,0,0);
    for (int x = 0; x < W; ++x) {
        for (int y = 0; y < H; ++y) {
            if (pix[x][y] != MAXZ) {
                a = point(x, y, MAXZ - 650);
                a = tr.RotatePoint(a, _light.param);
                if (a.x < 0 || a.x > 799 || a.y < 0 || a.y > 599) continue;
                shadBool[a.x][a.y] = 1;
            }
        }
    }
    return shadBool;
}

vector<vector<double>> Painter::calculateShadowUpgrade(vector<vector<point>> input, light _light) {
    vector<vector<double>> pix = clearPIX(W, H, MAXZ);
    vector<vector<double>> shadow = clearPIX(W, H, MAXZ);
    int ymax = 0, ymin = 0, ysc = 0, e1 = 0, e = 0;
    for (auto part: input) {
        int N = static_cast<int>(part.size());
        for (int i = 0; i < N; ++i) {
            part[i].x += W/2;
            part[i].y += 30; //* 2;
            //part[i].z += 400;
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
        double x1 = 0, x2 = 0;
        int xsc1 = 0, xsc2 = 0;
        double z1 = 0, z2 = 0, tc = 0, z = 0;
        ymin = floor(ymin);
        ymax = ceil(ymax);
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
            x1 = floor(x1);
            x2 = ceil(x2);
            if (x1 <= 0 || x2 >= W) continue;
            xsc1 = ( x1 < 0 ) ? 0 : x1;
            xsc2 = ( x2 < W ) ? x2 : W;
            for (double xsc = xsc1; xsc <= xsc2; xsc++) {
                tc = double(x1 - xsc) / (x1 - x2);
                z = z1 + tc * ( z2 - z1 );
                if (z < pix[xsc][ysc]) {
                    pix[xsc][ysc] = z;
                }
            }
        }
    }
    Transform tr;
    point a(0,0,0);
    for (int x = 0; x < W; ++x) {
        for (int y = 0; y < H; ++y) {
            if (pix[x][y] != MAXZ) {
                a = point(x, y, pix[x][y] + 300);
                a = tr.RotatePoint(a, _light.param);
                if (a.x < 0 || a.x > 799 || a.y < 0 || a.y > 599) continue;
                shadow[a.x][a.y] = a.z;
            }
        }
    }
    return shadow;
}

QImage Painter::drawLight(QImage img, light _light) {
    QColor col = _light.color;
    if (_light.color == "black")
        col = "yellow";
    int r,g,b;
    col.getRgb(&r, &g, &b);
    r = _light.intens*r;
    g = _light.intens*g;
    b = _light.intens*b;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    col = QColor(r, g, b);
    double xp = _light.param[0], yp = _light.param[1];
    if (xp > 0 && yp > 0) {
        for (int x = 0; x <= LIGHTRAD; ++x) {
            for (int y = 0; y <= sqrt(LIGHTRAD * LIGHTRAD - x*x); ++y) {
                    img.setPixelColor(x, H - 1 - y, col);
            }
        }
    } else if (xp > 0 && yp < 0) {
        for (int x = 0; x <= LIGHTRAD; ++x) {
            for (int y = 0; y <= sqrt(LIGHTRAD * LIGHTRAD - x*x); ++y) {
                    img.setPixelColor(W - 1 - x, H - 1 - y, col);
            }
        }
    } else if (xp < 0 && yp > 0) {
        for (int x = 0; x <= LIGHTRAD; ++x) {
            for (int y = 0; y <= sqrt(LIGHTRAD * LIGHTRAD - x*x); ++y) {
                    img.setPixelColor(x, y, col);
            }
        }
    } else if (xp < 0 && yp < 0) {
        for (int x = 0; x <= LIGHTRAD; ++x) {
            for (int y = 0; y <= sqrt(LIGHTRAD * LIGHTRAD - x*x); ++y) {
                    img.setPixelColor(W - 1 - x, y, col);
            }
        }
    }
    return img;
}

