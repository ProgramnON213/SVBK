#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main () {

    float m;
    cout << "Enter magnitude: ";
    cin >> m;
    double e = pow(10, (1.5*m+4.8));
    cout << "The energy released is " << setprecision(2) << fixed << e << " joules" << endl;

    return 0;   
}