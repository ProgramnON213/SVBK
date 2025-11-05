#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int n_org = n;

    if (n < 100 || n > 999) cout << "Please enter a 3-digit number only.";
    else {
        int d1, d2, d3;
        d1 = n%10;
        n /= 10;
        d2 = n%10;
        n /= 10;
        d3 = n%10;

        int sum = d1 + d2 + d3;
        int product = d1 * d2 * d3;

        if (sum == product) cout << n_org << " is a Spy Number.";
        else cout << n_org << " is NOT a Spy Number.";
    }

    return 0;
}
