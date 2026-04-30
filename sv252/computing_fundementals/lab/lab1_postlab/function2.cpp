#include <iostream>
using namespace std;

int convertToBaseM(int n, int m = 2) {
    // Write your code 
    int step = 1;
    int num = 0;
    while (n != 0) {
        num += (n % m) * step;
        step *= 10;
        n /= m;
    }
    return num;
}

int main() {
    int n;
    cin >> n;
    cout << convertToBaseM(n, 4) << '\n';
    cout << convertToBaseM(n, 8) << '\n';
    cout << convertToBaseM(n);
}