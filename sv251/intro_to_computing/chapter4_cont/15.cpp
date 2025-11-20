#include <iostream>
using namespace std;

int main() {
    int password = 1234;
    int i = 0;
    int input;
    bool accessGranted = false;
    do {
        cout << "Enter password: ";
        cin >> input;
        i++;
        if (input == password) accessGranted = true;
    } while (i < 3 && input != password);
    if (accessGranted) cout << "Access Granted!" << endl;
    else cout << "Access Denied!" << endl;
}