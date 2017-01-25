

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "filelib.h"
#include "simpio.h"

using namespace std;

void hailstone(int n) {
    cout << n << endl;
    if(n == 1) {
        return;
    } else {
        if(n % 2 == 0) {
            // n is even so we repeat the process with n/2
            hailstone(n / 2);
        } else {
            // n is odd so we repeat the process with 3 * n + 1
            hailstone(3 * n + 1);
        }
    }
}

int main() {
    cout << "Recursive Hailstone" << endl;
    while(true) {
        int startNumber = getInteger("Enter a start number (0 to exit): ");
        if(startNumber == 0) break;
        hailstone(startNumber);
    }
    cout << "Done!" << endl;
    return 0;
}



