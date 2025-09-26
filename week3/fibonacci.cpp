#include <iostream>
using namespace std;

int recursive_fibonacci(int n);

int main() {
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;
    cout << "The " << n << " of the Fibonacci is " << recursive_fibonacci(n) << endl;
    return 0;
}

int recursive_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return recursive_fibonacci(n-1) + recursive_fibonacci(n-2);
}