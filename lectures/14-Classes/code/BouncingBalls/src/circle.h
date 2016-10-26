#pragma once

#include "gwindow.h"
#include "gobjects.h"

const int SIZE = 30;

class Circle {
public:
    // adds a blue circle to the screen at a given (x,y)
    void add(GWindow & window, double x, double y);

    // moves the circle by dx, dy pixels
    void move(double dx, double dy);

    // returns the diameter of the circle
    double getSize();

    // returns the x pixel location
    double getX();

    // returns the y pixel location
    double getY();

private:
    // Dont look at me!
    // This is my private space. You gotta respect that
    // Why are you still reading?
    // Oh god what is that * about?
    GOval * oval;
}; // gotta have that semi-colon
