#include <iostream>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0)     cout << "Invalid input. All sides must be positive.";
    else if (a + b <= c || a + c <= b || b + c <= a)  cout << "The given sides do not form a triangle.";
    else {
        if (a == b && b == c)       cout << "The triangle is Equilateral.";
        else if (a == b || a == c || b == c)    cout << "The triangle is Isosceles.";
        else    cout << "The triangle is Scalene.";
    }
    
    return 0;
}