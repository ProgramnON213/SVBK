#include <iostream>
using namespace std;

int findOccurrences(int nums[], int size, int element) {
    // TODO
    if (size == 1 || size == 0) {
        if (nums[0] == element) {return 1;}
        else {return 0;}
    }
    if (nums[0] == element) {return 1 + findOccurrences(nums+1, size-1, element);}
    else {return findOccurrences(nums+1, size-1, element);}
}

int main() {
    int nums[] = {3,3,3};
    cout << findOccurrences(nums, 3, 1);
}