#include <iostream>
using namespace std;

int main () {
    double a, b, c;
    cout << "Enter 3 angles one by one: ";
    cin >> a >> b >> c;

    double d = 360-a-b-c;

    if (a==c && b==d) {
        if (a==90) {
            cout << "rectangle" << endl;
        } else {
            cout << "parallelogram" << endl;
        }
    } else if (a+b==180 || a+c==180) {
        if (a==90 || b==90 || c==90) {
            cout << "right trapezoid" << endl;
        } else if (a==b || a==c) {
            cout << "isosceles trapezoid" << endl;
        } else {
            cout << "normal trapezoid" << endl;
        }
    } else {
        cout << "irregular quadrilateral" << endl;
    }

    if (a+c==180 && b+d==180) {
        cout << "cyclic quadrilateral" << endl;
    }

    return 0;
}