#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main() {
    double n;
    cout << "Input your number: ";
    cin >> n;

    int num_of_digit = log10(n) + 1;

    cout << setw(3*(num_of_digit+3)/2) << "" << setprecision(1) << fixed << n << endl;
    cout << setw(2*(num_of_digit+3)/2) << "" << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << endl;
    cout << setw(1*(num_of_digit+3)/2) << "" << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << endl;
    cout << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << " " << setprecision(1) << fixed << n << endl;

    return 0;
}

/*
1st row has: numdigit + 2
2nd row has: (numdigit + 2)*2 + 1
3rd row has: (numdigit + 2)*3 + 2
4th row has: (numdigit + 2)*4 + 3
First row space: (4th-1st)/2 = 3(numdigit + 3)/2
Second row space: (4th - 2nd)/2 = 2(numdigit + 3)/2
                                = 1(numdigit + 3)/2
*/ 