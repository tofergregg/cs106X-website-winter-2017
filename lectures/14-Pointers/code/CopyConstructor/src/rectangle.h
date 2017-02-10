#pragma once

class Rectangle {
public:
    Rectangle(double width = 1, double height = 1); // constructor
    Rectangle(const Rectangle &src); // copy constructor

    ~Rectangle(); // destructor

    double area();
    double perimeter();
    double getHeight();
    double getWidth();

private:
    double *height;
    double *width;
};
