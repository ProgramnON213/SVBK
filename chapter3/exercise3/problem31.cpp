#include <iostream>
#include <math.h>
using namespace std;

int main() {
    double e;
    cout << "Enter the energy: ";
    cin >> e;
    double m;
    m = log10(e);
    m = m-4.8;
    m = m/1.5;
    cout << "The magnitude is: " << m << endl;

    return 0;
}