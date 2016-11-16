
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


int main() {
    setConsoleFont("courier-24");

    BasicGraph graph;
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");

    graph.addEdge("B", "A");
    graph.addEdge("B", "C");
    graph.addEdge("C", "B");

    cout << graph.toString() << endl;

    return 0;
}
