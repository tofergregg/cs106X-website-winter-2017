#include "circle.h"

void Circle::add(GWindow & w, double x, double y) {
    oval = new GOval(SIZE, SIZE);
    oval->setLocation(x, y);
    oval->setFilled(true);
    oval->setFillColor("blue");
    w.add(oval);
}

double Circle::getSize() {
    return SIZE;
}

void Circle::move(double dx, double dy) {
    oval->move(dx, dy);
}

double Circle::getX() {
    return oval->getX();
}

double Circle::getY() {
    return oval->getY();
}
