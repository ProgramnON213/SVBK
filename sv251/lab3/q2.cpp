#include <iostream>
using namespace std;

bool isPerfect (int n);

int main() {
    int N;
    bool found = false;
    cin >> N;
    
    for (int i = 1; i <= N; i++) {
        if (isPerfect(i)) {
            cout << i << endl;
            found = true;
        }
    }

    if (!(found)) cout << "No perfect numbers are found.";
    
    return 0;
}

bool isPerfect (int n) {
    if (n > 8128)   return false;
    int sum = 0;
    for (int i = 1; i <= n/2; i++) {
        if (n%i == 0)   sum += i;
    }
    return (n == sum);
}
