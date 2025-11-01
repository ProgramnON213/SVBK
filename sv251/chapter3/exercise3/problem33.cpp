#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main () {
    const double pi = 3.141592653589793;
    float a, theta;
    cout << "Enter amplitude: ";
    cin >> a;
    cout << "Enter angle: ";
    cin >> theta;
    double h = a * sin(theta/180 * pi);
    cout << "The height is " << setprecision(2) << fixed << h << " meters" << endl;

    return 0;   
}