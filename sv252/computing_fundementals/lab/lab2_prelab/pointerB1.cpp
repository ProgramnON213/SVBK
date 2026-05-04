#include <iostream>
using namespace std;

#include <new>
int* zeros(int n) {
    // TODO
    if (n < 1) {return nullptr;}
    int *arr = new (nothrow) int[n] ();
    return arr;
}

int main() {
    int*test0 = zeros(5);
}