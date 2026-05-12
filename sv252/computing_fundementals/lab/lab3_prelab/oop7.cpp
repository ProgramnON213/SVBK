#include <iostream>
using namespace std;

class ClockType
{
   public:
      ClockType(int, int, int); //constructor with parameters
      ClockType(); //default constructor
      
      void printTime() const;

   private:
      int hr;
      int min;
      int sec;
};

void ClockType::printTime() const { 
    if (hr < 10) 
        cout << "0"; 
    cout << hr << ":"; 
    if (min < 10) 
        cout << "0"; 
    cout << min << ":"; 
    if (sec < 10) 
        cout << "0"; 
    cout << sec;
}

//TODO
ClockType::ClockType(int hr, int min, int sec) {
    if (hr < 0 || hr >= 24) {hr = 0;}
    if (min < 0 || min >= 60) {min = 0;}
    if (sec < 0 || sec >= 60) {sec = 0;}
    
    this->hr = hr;
    this->min = min;
    this->sec = sec;
}

ClockType::ClockType() {
    this->hr = 0;
    this->min = 0;
    this->sec = 0;
}