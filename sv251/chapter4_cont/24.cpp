#include <iostream>
using namespace std;

int main() {
    int lower, upper;
    cout << "Enter lower and upper bound: ";
    cin >> lower >> upper;
    for (int n=lower; n<=upper; n++) {
        bool isPrime = true;
        for (int i=2; i<n; i++) {
            if (n%i==0) isPrime = false;
        }
        if (isPrime) cout << n << " ";
    }
    cout << endl;
}