#include "ball.h"
#include "random.h"

Ball::Ball() {
    dx = randomReal(-DELTA_MAX, DELTA_MAX);
    dy = randomReal(-DELTA_MAX, DELTA_MAX);
}

void Ball::addToScreen(GWindow &window) {
    double x = window.getWidth() / 2;
    double y = window.getHeight() / 2;
    blueCircle.add(window, x, y);
}

void Ball::takeStep(int screenWidth, int screenHeight) {
    if(blueCircle.getX() < DELTA_MAX || blueCircle.getX() > screenWidth - blueCircle.getSize()) {
        dx *= -1;
    }
    if(blueCircle.getY() < DELTA_MAX || blueCircle.getY() > screenHeight - blueCircle.getSize()) {
        dy *= -1;
    }
    blueCircle.move(dx, dy);
}

ostream& operator<<(ostream& out, Ball& ball){
    out << ball.dx << ", " << ball.dy;
    return out;
}
