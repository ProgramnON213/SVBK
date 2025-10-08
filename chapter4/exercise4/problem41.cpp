#include <iostream>
using namespace std;

int main () {
    double a, b, c;
    cout << "Input length one by one: ";
    cin >> a >> b >> c;
    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "INVALID LENGTHS" << endl;
    } else if (a+b>c && a+c>b && b+c>a) {
        if (a==b && b==c) {
            cout << "EQUILATERAL TRIANGLE" << endl;
        } else if (a==b || b==c || c==a) {
            cout << "ISOSCELES TRIANGLE" << endl;
        } else {
            cout << "SCALENE TRIANGLE" << endl;
        }
    } else {
        cout << "INVALID TRIANGLE" << endl;
    }
    return 0;
}