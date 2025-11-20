#include <iostream>
using namespace std;

int main() {
    int n, sum = 0;
    cout << "Input number: ";
    cin >> n;
    for (int i=1; i<=n; i++) {
        cout << i << " ";
        sum += i;
    }
    cout << endl;
    cout << "The sum is " << sum << endl;
}