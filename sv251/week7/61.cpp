#include <iostream>
using namespace std;

int main() {
    int steps = 0;
    long n;
    cout << "Input a number: ";
    cin >> n;

    do {
        if (n%2==0) n/=2;
        else n=3*n+1;
        steps++;
    } while (n != 1);
    cout << steps << endl;

    return 0;
}