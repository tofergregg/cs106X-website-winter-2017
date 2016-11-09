#include "LinkedList.h"

int main() {
    LinkedList list;
    list.insert("pi",3.1415926535);
    list.insert("e",2.7182818);
    list.insert("zero",0.0);
    list.insert("one",1.0);
    list.insert("negative one", -1.0);
    list.insert("square root of 2",1.4142);
    cout << list << endl;
    return 0;
}
