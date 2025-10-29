#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    if (n==0) cout << "1" << endl;
    else {
        int count = 0;
        while (n!=0) {
            n /= 10;
            count++;
        }
        cout << count << endl;
    }
}