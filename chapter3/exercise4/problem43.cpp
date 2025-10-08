#include <iostream>
#include <string.h>
using namespace std;

int main() {
    // Take from n_index till the end right?
    string full_name;
    int n;
    cout << "Enter full name: ";
    getline(cin, full_name);
    cout << "Enter index n: ";
    cin >> n;
    string last_name(full_name, n+1);
    cout << "Last name is: " << last_name << endl;
    return 0;
}