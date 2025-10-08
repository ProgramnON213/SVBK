#include <iostream>
using namespace std;

int main () {
    double a, b, c;
    cout << "Input length one by one: ";
    cin >> a >> b >> c;
    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "INVALID LENGTHS" << endl;
    } else if (a+b>c && a+c>b && b+c>a) {
        cout << "VALID TRIANGLE" << endl;
    } else {
        cout << "INVALID TRIANGLE" << endl;
    }
    return 0;
}