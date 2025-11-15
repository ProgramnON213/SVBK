#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    double ans = 0;
    
    if (n < 1) cout << "Error: n must be a positive integer.";
    else {
        for (int i = 1;i <= n; i++) {
            ans += 1 / (pow(i, i));
        }
        if (n == 1 || n == 2) cout << ans;
        else    cout << setprecision(6) << fixed << ans;
    }

    return 0;
}