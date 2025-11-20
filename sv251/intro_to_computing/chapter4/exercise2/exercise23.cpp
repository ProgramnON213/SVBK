#include <iostream>
using namespace std;

const int FULL_FARE = 20000;
const float DISCOUNT_RATE = 0.75;

int main () {
    int age;
    cout << "Enter age: ";
    cin >> age;
    string id;
    cout << "Enter id: ";
    cin >> id;
    string type(id, 6);
    int price;
    if (type == "DISABLED" || age <7 || age >= 60) {
        price = FULL_FARE * (1 - DISCOUNT_RATE); 
    } else {
        price = FULL_FARE;
    }
    cout << price << endl;
    return 0;
}