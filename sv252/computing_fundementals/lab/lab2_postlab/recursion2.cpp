#include <iostream>
#include <math.h>
using namespace std;

int countWays(int sumToReach, int candidate) {
    if (sumToReach < 0) {return 0;}
    else if (sumToReach == 0) {return 1;}
    else if (candidate == 0) {return 0;}

    return countWays(sumToReach - candidate*candidate, candidate-1) + countWays(sumToReach, candidate-1);
}

int countWaySumOfSquare(int x) {
    if (x == 0) {return 0;}
    int start = sqrt(x);
    return countWays(x, start);
}

int main() {
    int n;
    cin >> n;
    cout << countWaySumOfSquare(n);
}