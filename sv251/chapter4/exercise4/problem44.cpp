#include <iostream>
#include <cmath>
using namespace std;

const double EP = 0.00001;

int main () {
    double a, b, c;
    cout << "Input coefficient one by one: ";
    cin >> a >> b >> c;
    if (a==0) {
        cout << "Invalid quadratic expression" << endl;
    } else {
        double delta = b*b - 4*a*c;
        if (abs(delta) <= EP) { // this is delta == 0
            cout << "One real solution " << -b/(2*a) << endl;
        } else if (delta > 0) {
            double x1 = (-b+sqrt(delta))/(2*a);
            double x2 = (-b-sqrt(delta))/(2*a);
            cout << "Two solutions are " << x1 << " and " << x2 <<endl;
        } else {
            cout << "No real solution" << endl;
        }
    }
    return 0;
}