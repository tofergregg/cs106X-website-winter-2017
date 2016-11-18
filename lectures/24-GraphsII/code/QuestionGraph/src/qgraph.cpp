#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "pqueue.h"
#include "basicgraph.h"

using namespace std;

int NUM_NODES = 20;
int NUM_NEIGHBORS = 3;

int main() {

    Map<int, Set<int>> edges;

    for(int i = 0; i < NUM_NODES; i++) {
        cout << "vertex: " << i << endl;
        cout << "neighbors: " << endl;
        Set<int> neighbors;
        for(int j = 0; j < NUM_NEIGHBORS; j++) {
            while(true) {
                int neighbor = randomInteger(0, NUM_NODES - 1);
                if(!neighbors.contains(neighbor) && neighbor != i) {
                    neighbors.add(neighbor);
                    cout << neighbor << " ";
                    break;
                }
            }
        }
        edges.add(i, neighbors);
        cout << endl << endl;
    }

    for(int key : edges) {
        for(int n : edges[key]) {
            cout << key << " " << n << endl;
        }
    }

    return 0;
}
