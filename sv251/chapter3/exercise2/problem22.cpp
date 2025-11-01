#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    string name;
    int age;
    cout << "Your name is: ";
    cin >> name;
    cout << "You age is: ";
    cin >> age;

    cout << "******************************" << endl;
    cout << "* " << left << setw(26) << ("Name: " + name) << " *" << endl;
    cout << "* " << left << setw(26) << ("Age: " + to_string(age)) << " *" << endl;
    cout << "******************************" << endl;

    return 0;
}