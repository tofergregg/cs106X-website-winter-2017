#ifndef DATE
#define DATE
#include <iostream>
using namespace std;

// yay we have a new variable type! Happy date.
class Date {
public:
    // how someone makes a new date...
    Date(int day, int month, int year);

    // what happens when we destroy a date.
    ~Date();

    // clients can call these on a date
    int getDay();
    int getMonth();
    int getYear();
    void incrementDay();
    int daysUntil(Date future);

    // some operator overloading
    friend ostream& operator<<(ostream& out, Date& date);
    friend bool operator !=(const Date & d1, const Date & d2);
    friend bool operator ==(const Date & d1, const Date & d2);
    friend bool operator <(const Date & d1, const Date & d2);
    friend bool operator <=(const Date & d1, const Date & d2);

private:
    int daysInMonth();
    bool isLeapYear();

    int day;
    int month;
    int year;
};



#endif // DATE
