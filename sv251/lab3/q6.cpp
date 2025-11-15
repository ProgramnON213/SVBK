#include <iostream>
#include <cmath>
using namespace std;

double factorial(int n);

int main() {
    int n;
    double x, ans = 0;

    cin >> x >> n;

    if (n == 0) cout << 1;
    else {
    for (int i = 0; i < n; i++) {
        double sign;
        if (i%2==0) sign = 1;
        else sign = -1;
        ans += sign * pow(x, 2*i) / factorial(2*i);
    }

    cout << ans;
    }

    return 0;
}

double factorial(int n) {
    double result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}
