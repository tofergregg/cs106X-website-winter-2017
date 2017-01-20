// Queue mystery

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h"

using namespace std;

int main() {
    Queue<int> queue;
    // produce: {1, 2, 3, 4, 5, 6}
    for (int i = 1; i <= 6; i++) {
        queue.enqueue(i);
    }
    // original mystery:
    for (int i = 0; i < queue.size(); i++) {
        cout << queue.dequeue() << " ";
    }

    // better idiom:
    /*
    while (!queue.isEmpty()) {
        cout << queue.dequeue() << " ";
    }
    */

    // okay idiom if you want to go through original queue elements once:
    /*int origQSize = queue.size();
    for (int i=0; i < origQSize; i++) {
        int value = queue.dequeue();
        cout << value << " ";
        // re-enqueue even values
        if (value % 2 == 0) {
            queue.enqueue(value);
        }
    }*/

    cout << queue.toString() << "  size " << queue.size() << endl;

    return 0;
}
