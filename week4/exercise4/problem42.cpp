#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // Take the first p character right??
    string full_name;
    int p;
    cout << "Enter full name: ";
    getline(cin, full_name);
    cout << "Enter length p: ";
    cin >> p;
    string first_name(full_name, 0, p);
    cout << "First name is: " << first_name << endl;
    return 0;
}