#include <iostream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "rectangle.h"

using namespace std;

// Rectangle example

#include <iostream>
#include "console.h"

using namespace std;

int main() {
    Rectangle r(3,4);
    cout << "Width: " << r.getWidth() << ", ";
    cout << "Height: " << r.getHeight() << endl;

    cout << "Area: " << r.area() << endl;
    cout << "Perimeter: " << r.perimeter() << endl;

    // let's make a copy:
    Rectangle r2 = r;

    return 0;
}
