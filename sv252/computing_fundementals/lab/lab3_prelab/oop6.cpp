#include <iostream>
using namespace std;

class Room
{
    private:
    float length;
    float breadth;
    float height;
    
    public:
    Room();
    Room(float l, float b, float h);
    float calculateArea() const;
    float calculateVolume() const;
};

Room::Room() {
    length = 0;
    breadth = 0;
    height = 0;
}

Room::Room(float l, float b, float h) {
    length = l;
    breadth = b;
    height = h;
}

float Room::calculateArea() const {
    return length * breadth;
}

float Room::calculateVolume() const {
    return length * breadth * height;
}