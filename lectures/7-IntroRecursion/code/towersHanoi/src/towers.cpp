

#include <fstream>
#include <iostream>
#include <iomanip>
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
#include "ghanoi.h"

using namespace std;

static const int N = 5;


void findSolution(int n, char source, char target, char aux) {
    // All about that base
    if(n == 1) {
        moveSingleDisk(source, target);
    // Recursive case
    } else {
        findSolution(n - 1, source, aux, target);
        moveSingleDisk(source, target);
        findSolution(n - 1, aux, target, source);
    }
}

int main() {
    cout << "Towers of Hanoi" << endl;
    initHanoiDisplay(N);
    findSolution(N, 'a', 'c', 'b');
    return 0;
}

