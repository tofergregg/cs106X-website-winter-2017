// This program demonstrates solves the knapsack problem

// By: Chris Gregg
// Date: February 1, 2017

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

// objectT struct
struct objectT {
    int weight;
    int value;
};

// function prototypes
int FillKnapsack(Vector<objectT> &objects, int targetWeight);
int FillKnapsack(Vector<objectT> &objects, int weight, int score);

int main() {
    // solution: 44
    int values[] = {12,10,8,11,14,7,9};
    int weights[] = {4,6,5,7,3,1,6};
    int targetWeight = 18;

    // solution: 67
    //int values[] = {5,20,3,50,5,4,15,12,6,7};
    //int weights[] = {6,15,11,12,6,11,13,7,17,13};
    //int targetWeight = 25;

    // solution: 7
    //int values[] = {3,4,5,6};
    //int weights[] = {2,3,4,5};
    //int targetWeight = 5;

    int numItems = sizeof(values) / sizeof(int);

    Vector<objectT> testObjects;

    for (int i=0; i < numItems; i++) {
        objectT object;
        object.value = values[i];
        object.weight = weights[i];
        testObjects.add(object);
    }

    cout << "Best solution has a best score of: "
         << FillKnapsack(testObjects, targetWeight) << endl;
    return 0;
}

int FillKnapsack(Vector<objectT> &objects, int targetWeight) {
    return FillKnapsack(objects,targetWeight,0);
}

int FillKnapsack(Vector<objectT> &objects, int weight, int bestScore) {
    if (weight < 0) return 0; // we tried too much weight!
        int localBestScore = bestScore;
        int obSize = objects.size();
        for (int i = 0; i < obSize; i++) {
            objectT originalObject = objects[i];
            int currValue = bestScore + originalObject.value;
            int currWeight = weight - originalObject.weight;
            // remove object for recursion
            objects.remove(i);
            currValue = FillKnapsack(objects,currWeight,currValue);
            if (localBestScore < currValue) {
                localBestScore = currValue;
            }
            // replace
            objects.insert(i,originalObject);
        }
        return localBestScore;
}

