#include<iostream>
#include<string>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

/* END of library */


int gcdRecursion(int p, int q) {
    // BEGIN YOUR IMPLEMENTATION [1]
    // TODO
    int small = min(p, q);
    int big = max(p, q);
    if (big%small == 0) {return small;}
    return gcdRecursion(small, big%small);
    // END YOUR IMPLEMENTATION [1]
}

int gcdIteration(int p, int q) {
    // BEGIN YOUR IMPLEMENTATION [2]
    // TODO
    int small = min(p, q);
    int max = 1;
    for (int i = 2; i <= small; i++) {
        if (p%i==0 && q%i==0) {
            max = i;
        }
    }
    return max;
    // END YOUR IMPLEMENTATION [2]
    }

int main()
{
    int p,q;
    cin>>p>>q;
    cout<<gcdRecursion(p,q)<< " "<<gcdIteration(p,q);
    return 0;
}