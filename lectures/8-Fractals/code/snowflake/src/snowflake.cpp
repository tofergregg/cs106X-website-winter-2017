

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
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = SCREEN_WIDTH;
static const int BASE_Y = SCREEN_HEIGHT - SCREEN_HEIGHT * .4;
static const int BASE_LEFT_X = 170;
static const int BASE_RIGHT_X = SCREEN_WIDTH - 170;

/* Function: Interpolate
 * ---------------------
 * Given two points and a franction (assumed to be in the range
 * [0, 1], the function returns the point "fraction" amount of the
 * way between p1 and p2.
 */
GPoint interpolate(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.getX() - p1.getX();
    double deltaY = p2.getY() - p1.getY();
    double x = p1.getX() + fraction * deltaX;
    double y = p1.getY() + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}

/* Method: Equilatoral Tip
 * -----------------------
 * Given two points of an equilateral triangle, this method returns the third.
 * It assumes that the first paramenter is the bottom left of the triangle
 */
GPoint equilatoralTip(GPoint p1, GPoint p2) {
    double deltaX = (p2.getX() - p1.getX());
    double deltaY = (p2.getY() - p1.getY());
    double x = p1.getX() + (deltaX*COS_60 + deltaY*SIN_60);
    double y = p1.getY() + (deltaY*COS_60 - deltaX*SIN_60);
    GPoint tip(x, y);
    return tip;
}

/* Method: Draw Flake Line
 * -----------------------
 * Recursively draws a snowflake line (with a given level).
 */
void drawFlakeLine(GWindow & window, int level, GPoint start, GPoint end) {
    // your code here...
}

/* Draw a Snowflake using recursive draw flake line.
 *         Top
 *          X
 *         / \
 *        /   \
 *       /     \
 *      X-------X
 *BottomLeft   BottomRight
 */
int main() {
    int depth = 10;

    GWindow w(SCREEN_WIDTH, SCREEN_HEIGHT);
    GPoint bottomLeft(BASE_LEFT_X, BASE_Y);
    GPoint bottomRight(BASE_RIGHT_X, BASE_Y);
    GPoint top = equilatoralTip(bottomLeft, bottomRight);
    drawFlakeLine(w, depth, bottomLeft, bottomRight);
//    drawFlakeLine(w, depth, bottomLeft, top);
//    drawFlakeLine(w, depth, top, bottomRight);
//    drawFlakeLine(w, depth, bottomRight, bottomLeft);
    return 0;
}

