#include <iostream>
#include <string.h>
using namespace std;

int main() {
    string code;
    cout << "Enter code: ";
    cin >> code;
    string pd(code, 4);
    cout << "Product Detail is: " << pd << endl;
    return 0;
}