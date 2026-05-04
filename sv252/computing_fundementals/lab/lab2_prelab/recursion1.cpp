#include <iostream>
using namespace std;

int calculate_power(int n, int e) { 
    if (e == 0) {return 1;}
    else {return calculate_power(n, e-1)*n;}
}

int main() {
    int n = 2;
    int e = 3;
    cout << calculate_power(n ,e);
}