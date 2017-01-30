/*
 * CS 106X, Chris Gregg 
 * This program demonstrates how to use recursion
 * to crawl a file directory
 */

#include <fstream>
#include <iostream>
#include "console.h"
#include "vector.h"
#include "filelib.h"
#include "simpio.h"

using namespace std;
// function prototypes
void crawl(string path);

int main() {
    string root = getLine("Please enter a directory: ");

    cout << "looking..." << endl;

    crawl(root);

    cout << "done" << endl;
    return 0;
}

void crawl(string path) {
    // base case
    if (isFile(path)) {
        cout << path << endl;
        return;
    }
    // recursive case
    Vector<string> contents;
    listDirectory(path, contents); // populates contents with the directory listing
    for (string element : contents) {
        // make a recursive call for each element
        string newPath = path + "/" + element;
        crawl(newPath);
    }
}
