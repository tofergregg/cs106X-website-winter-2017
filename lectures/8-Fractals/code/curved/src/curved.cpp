

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "console.h"
#include "timer.h"
#include "hashset.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
#include "vector.h"
#include "grid.h"
#include "filelib.h"
#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"
#include "point.h"

using namespace std;

// useful math constants
static const double COS_60 = 0.5;            //value of cos(60 degrees)
static const double SIN_60 = sqrt(3)*0.5;    //value of sin(60 degrees)

// display constants
static const int SCREEN_WIDTH = 500;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;
static const int BASE_Y = 450;
static const int BASE_X = 250;


double degreesToRadians(double degrees) {
    double radiansPerDegree = 2. * M_PI / 360;
    return degrees * radiansPerDegree;
}

GPoint addPolar(GPoint start, double length, double angleDegrees) {
    double radians = degreesToRadians(angleDegrees);
    double dx = length * cos(radians);
    double dy = length * sin(radians);
    GPoint next(start.getX() + dx, start.getY() - dy);
    return next;
}

void drawCenteredCircle(GWindow & w, GPoint center, double radius) {
    w.drawOval(center.getX() - radius, center.getY() - radius, radius * 2, radius * 2);
}

void drawCurve(GWindow & w, int level, GPoint base, double radius, double length, double angle) {
    if(level > 0) {
        drawCenteredCircle(w, base, radius);

        GPoint newBase = addPolar(base, length, angle);
        angle = angle - 20;
        radius = radius * 0.8;
        length = length * 0.8;
        drawCurve(w, level - 1, newBase, radius, length, angle);

    }
}


int main() {
    int depth = 100;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint center(100, 400);
    drawCurve(w, depth, center, 50, 100, 70);
    return 0;
}

