#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "console.h"
#include "timer.h"
#include "vector.h"
#include "grid.h"
#include "filelib.h"
#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"
#include "point.h"
#include "ball.h"

using namespace std;

const int NUM_BALLS = 1;

void createBalls(Vector<Ball> & balls, GWindow & w) {
    for(int i = 0; i < NUM_BALLS; i++) {
        // make a brand new ball
        Ball newBall;

        // add the ball to the screen
        newBall.addToScreen(w);

        // add the ball to the vector of balls
        balls.add(newBall);
    }
}

void moveBalls(Vector<Ball> & balls, GWindow & w) {
    for(int i = 0; i < balls.size(); i++) {
        balls[i].takeStep(w.getWidth(), w.getHeight());
    }
}

int main() {
    GWindow window;

    Vector<Ball> balls;
    createBalls(balls, window);

    for(Ball ball : balls) {
        cout << ball << endl;
    }

    while(true) {
        moveBalls(balls, window);
        pause(10);
    }

    return 0;
}

