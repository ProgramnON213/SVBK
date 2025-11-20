#include <iostream>
using namespace std;

int max3(int a, int b, int c);

int main() {
    int a;  int b;  int c;
    cin >> a;   cin >> b;   cin >> c;
    cout << "The maximum number is " << max3(a, b, c) << endl;
    return 0;
}

int max3(int a, int b, int c) {
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b < c) {
        int temp = b;
        b = c;
        c = temp;
    }
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    return a;
}