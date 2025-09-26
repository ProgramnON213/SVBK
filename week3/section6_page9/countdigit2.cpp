#include <iostream>
using namespace std;

int countDigit2(long n);

int main() {
    cout << "Enter a number please: ";
    long n;
    cin >> n;
    cout << "The number you have just typed has " << countDigit2(n) << " digit(s)" << endl;
    return 0;
}

int countDigit2(long n) {
    int ans = 0;
    while (n!=0) {
        ans += 1;
        n /= 10;
    }
    return ans;
}