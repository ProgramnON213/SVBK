#include <iostream>
using namespace std;

int main () {
    int y;
    cout << "Enter year: ";
    cin >> y;
    if (y % 400 == 0) {
        cout << "This is a Leap Year" << endl;
    } else {
        if (y % 100 == 0) {
            cout << "This is NOT a Leap Year" << endl;
        } else {
            if (y % 4 == 0) {
                cout << "This is a Leap Year" << endl;
            } else {
                cout << "This is NOT a Leap Year" << endl;
            }
        }
    }
}