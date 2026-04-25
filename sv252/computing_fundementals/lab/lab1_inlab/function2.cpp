#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n == 2) {return true;}
    if (n%2 == 0 || n < 2) {return false;}
    int maxNumToCheck = n/2+1;
    for (int i = 3; i <= maxNumToCheck; i+=2) {
        if (n % i == 0) {return false;}
    }
    return true;
}

int takeTotalOfDigit(int n) {
    int total = 0;
    while (n != 0) {
        total += n % 10;
        n /= 10;
    }
    return total;
}

bool isSpecialNumber(int n) {
    // Write your code 
    return (isPrime(n) && isPrime(takeTotalOfDigit(n)));
}

int main() {
    cout << isSpecialNumber(23) << endl;
    cout << isSpecialNumber(51) << endl;
    cout << isSpecialNumber(11) << endl;
}