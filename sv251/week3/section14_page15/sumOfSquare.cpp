#include <iostream>
using namespace std;

int main() {
    long ans = 0;
    for (int i=0; i*i<=100; i++) {
        ans += i*i;
    }
    cout << ans << endl;
    return 0;
}