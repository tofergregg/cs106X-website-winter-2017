

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

// tree constants
static const double DECAY = 0.8;
static const int TRUNK_LENGTH = 80;
static const int LEAF_RADIUS = 5;

GPoint addPolar(GPoint start, double length, double angleDegrees) {
    double radiansPerDegree = 2. * M_PI / 360;
    double radians = angleDegrees * radiansPerDegree;
    double dx = length * cos(radians);
    double dy = length * sin(radians);
    GPoint next(start.getX() + dx, start.getY() - dy);
    return next;
}

void drawLeaf(GWindow & w, GPoint center) {
    double x = center.getX() - LEAF_RADIUS;
    double y = center.getY() - LEAF_RADIUS;
    //w.drawOval(x, y, LEAF_RADIUS * 2, LEAF_RADIUS * 2);
    double size = LEAF_RADIUS * 2;
    GOval * leaf = new GOval(x, y, size, size);
    leaf->setColor("#006400");
    leaf->setFilled(true);
    w.add(leaf);
}

void drawBranch(GWindow & w, GPoint start, GPoint end) {
    //w.drawLine(start, end);
    GPolygon * branch = new GPolygon();
    branch->addVertex(start.getX() - 3, start.getY());
    branch->addVertex(end.getX() - 3, end.getY());
    branch->addVertex(end.getX() + 3, end.getY());
    branch->addVertex(start.getX() + 3, start.getY());
    branch->setColor("#B8860B");
    branch->setFilled(true);
    w.add(branch);
}

void drawTree(GWindow & w, int level, GPoint base, double length, double angle) {
    if(level > 0) {
        GPoint top = addPolar(base, length, angle);
        drawBranch(w, base, top);
        drawTree(w, level - 1, top, length * DECAY, angle - 25);
        drawTree(w, level - 1, top, length * DECAY, angle + 25);
    } else {
        drawLeaf(w, base);
    }
}


int main() {
    int depth = 4;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint base(BASE_X, BASE_Y);
    drawTree(w, depth, base, TRUNK_LENGTH, 90);
    return 0;
}

