#include <iostream>
using namespace std;

int find_gcd (int m, int n);

int main() {
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;
    int m;
    cout << "Enter another positive integer: ";
    cin >> m;
    cout << "The greatest common divisor of " << m << " and " << n << " is " << find_gcd(m, n) << endl;
    return 0;
}

int find_gcd(int m, int n) {
    // Make sure m is larger than n
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    // euclidean algorithm
    int r = m % n;
    if (r == 0) {
        return n;
    }
    else {
        return find_gcd(n, r);
    }
}