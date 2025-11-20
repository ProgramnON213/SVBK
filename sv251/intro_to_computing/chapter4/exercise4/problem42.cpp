#include <iostream>
using namespace std;

int main () {
    int age;
    cout << "Enter your age: ";
    cin >> age;
    string permission;
    cout << "Have you asked your parent?(Y/N) ";
    cin >> permission;
    if (age >= 18) {
        cout << "You can join the event" << endl;
    } else if (permission == "Y") {
        cout << "You can join with permission" << endl;
    } else {
        cout << "You cannot join the event" << endl;
    }
    return 0;
}