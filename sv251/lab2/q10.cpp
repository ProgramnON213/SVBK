#include <iostream>
using namespace std;

int main() {
    int A, B;

    cin >> A >> B;

    int C = A;  A = B;  B = C;

    cout << A << " " << B;
    return 0;
}
