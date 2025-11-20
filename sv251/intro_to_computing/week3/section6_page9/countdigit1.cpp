#include <iostream>
using namespace std;

int countDigit1(long n);

int main() {
    cout << "Enter a number please: ";
    long n;
    cin >> n;
    cout << "The number you have just typed has " << countDigit1(n) << " digit(s)" << endl;
    return 0;
}

int countDigit1(long n) {
    if (n/10 == 0) {
        return 1;
    }
    return 1 + countDigit1(n/10);
}