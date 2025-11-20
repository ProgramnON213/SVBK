#include <iostream>
using namespace std;

int main() {
    int password = 1234;
    int i = 0;
    int input = password + 1;
    bool accessGranted = false;
    while (i < 3 && input != password) {
        cout << "Enter password: ";
        cin >> input;
        i++;
        if (input == password) accessGranted = true;
    }
    if (accessGranted) cout << "Access Granted!" << endl;
    else cout << "Access Denied!" << endl;
}