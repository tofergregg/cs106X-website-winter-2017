#include <iostream>
#include "console.h"
#include "StringSet.h"
using namespace std;

int main() {
    cout << "Creating Set of Strings" << endl;
    StringSet ss;

    cout << "Empty? " << (ss.isEmpty() ? "true" : "false") << endl;
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Adding \"cat\"" << endl;
    ss.add("cat");
    cout << "Empty? " << (ss.isEmpty() ? "true" : "false") << endl;
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Adding \"dog\"" << endl;
    ss.add("dog");
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Adding fish, zebra, aardvark, lion, meerkat, marmot, bird, eagle" << endl;
    ss.add("fish");
    ss.add("zebra");
    ss.add("aardvark");
    ss.add("lion");
    ss.add("meerkat");
    ss.add("marmot");
    ss.add("bird");
    ss.add("eagle");

    cout << "Count? " << ss.size() << endl << endl;

    cout << "Full set: " << ss << endl << endl;

    cout << "Contains \"fish\"? " << (ss.contains("fish") ? "true" : "false") << endl;
    cout << "Contains \"hamster\"? " << (ss.contains("hamster") ? "true" : "false") << endl;

    cout << "First in alphabet? " << ss.findMin() << endl;
    cout << "Last in alphabet? " << ss.findMax() << endl;

    cout << "Removing \"bird\"" << endl;
    ss.remove("bird");
    cout << "Full set: " << ss << endl << endl;
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Removing \"lion\"" << endl;
    ss.remove("lion");
    cout << "Full set: " << ss << endl << endl;
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Removing \"fish\"" << endl;
    ss.remove("fish");
    cout << "Full set: " << ss << endl << endl;
    cout << "Count? " << ss.size() << endl << endl;

    cout << "Removing \"cat\" (which is the root)" << endl;
    ss.remove("cat");
    cout << "Full set: " << ss << endl << endl;
    cout << "Count? " << ss.size() << endl << endl;
    return 0;
}
