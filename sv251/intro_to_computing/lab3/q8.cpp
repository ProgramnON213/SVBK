#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int sum = 0, temp_sum = 0;

    for (int i = 1; i <= n; i++) {
        temp_sum += i;
        sum += temp_sum;
    }

    cout << sum;
    
    return 0;
}