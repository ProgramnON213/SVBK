#include <iostream>
using namespace std;

int findMax(int x, int y);

int main() {
    cout << "Enter two numbers: ";
    int a, b, max;
    cin >> a >> b;
    max = findMax(a, b);
    cout << max << endl;
    return 0;
}

int findMax(int x, int y) {
    if (x >= y) return x;
    else return y;
}