#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main () {
    const double pi = 3.141592653589793;
    const double g = 9.81;
    float h, a;
    cout << "Enter water depth: ";
    cin >> h;
    cout << "Enter seabed slope angle: ";
    cin >> a;
    double v = sqrt(g*h*tan(a/180 * pi));
    cout << "The speed is " << setprecision(2) << fixed << v << " meters per second" << endl;
    return 0;   
}