#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int n_org = n;

    if (n >= -999 && n <= -100) n = -n;
    if (n < 100 || n > 999) cout << "Please enter a 3-digit number only.";
    else {
        int d1, d2, d3;
        d1 = n%10;
        n /= 10;
        d2 = n%10;
        n /= 10;
        d3 = n%10;

        int cubed = d1*d1*d1 + d2*d2*d2 + d3*d3*d3;

        if (cubed == n_org) cout << n_org << " is an Armstrong number.";
        else cout << n_org << " is NOT an Armstrong number.";
    }

    return 0;
}
