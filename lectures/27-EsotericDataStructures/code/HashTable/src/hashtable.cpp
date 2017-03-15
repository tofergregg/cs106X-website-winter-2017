#include <iostream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "string.h"
#include <ostream>
#include "vector.h"
#include <cmath>
#include "HashMapIntInt.h"

using namespace std;

int main() {
    HashMap map;
    map.put(3, 12);
    map.printTable();
    map.put(4, 11);
    map.printTable();
    map.put(77, 1);
    map.printTable();
    map.put(7, 8);
    map.printTable();
    map.put(5, 22);
    map.printTable();
    map.put(17, 3);
    map.printTable();
    map.put(19, 108);
    map.printTable();
    map.put(47, 100);
    map.printTable();
    map.put(44, 46);
    map.printTable();
    map.put(11, 22);
    map.printTable();
    map.put(2, 17);
    map.printTable();
    map.put(1, 19);
    map.printTable();
    map.put(11, 100);
    map.printTable();
    map.put(9, 181);
    map.printTable();
    map.remove(17);
    map.printTable();
    map.remove(181);
    map.printTable();
    if (map.containsKey(122)) {
        map.put(1, 1);
        map.printTable();
    } else {
        map.put(28, 3);
        map.printTable();
    }
    int x = 1;
    while (map.containsKey(3)) {
        if (map.containsKey(x)) {
            map.remove(x);
            map.printTable();
        }
        x++;
    }
    map.put(47, 100);
    map.printTable();
    cout << "Size: " << map.size() << endl;
    cout << "Capacity: " << map.capacity() << endl;
    cout << "Load Factor: " << map.loadFactor() << endl;
    return 0;
}
