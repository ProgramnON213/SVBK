#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);

int main() {
    int n;
    cin >> n;
    
    if (isPrime(n))   cout << "YES";
    else    cout << "NO";

    return 0;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n/2; i++) {
        if (n%i == 0)   return false;
    }
    return true;
}
