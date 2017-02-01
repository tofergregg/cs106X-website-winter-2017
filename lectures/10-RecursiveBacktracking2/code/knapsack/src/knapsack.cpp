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
    int NUM_ITEMS = 4;
    //int values[] = {5,20,3,50,5,4,15,12,6,7};

    //int weights[] = {6,15,11,12,6,11,13,7,17,13};
    int values[] = {3,4,5,6};
    int weights[] = {2,3,4,5};

    Vector<objectT> testObjects;

    for (int i=0; i < NUM_ITEMS; i++) {
        objectT object;
        object.value = values[i];
        object.weight = weights[i];
        testObjects.add(object);
    }

    cout << "Best solution has a best score of: "
         << FillKnapsack(testObjects, 5) << endl;
    return 0;
}

int FillKnapsack(Vector<objectT> &objects, int targetWeight) {
    return FillKnapsack(objects,targetWeight,0);
}

int FillKnapsack(Vector<objectT> &objects, int weight, int totalValue) {
    if (weight < 0) return 0; // we tried too much weight!
        int bestScore = totalValue;
        int obSize = objects.size();
        for (int i = 0; i < obSize; i++) {
            objectT originalObject = objects[i];
            int currValue = totalValue + originalObject.value;
            int currWeight = weight -= originalObject.weight;
            if (bestScore < currValue) {
                bestScore = currValue;
                //cout << bestScore << endl;

            }
            // remove object for recursion
            objects.remove(i);
            currValue = FillKnapsack(objects,currWeight,currValue);
            if (bestScore < currValue) {
                bestScore = currValue;
            }
            // replace
            objects.insert(i,originalObject);
        }
        return bestScore;
}

