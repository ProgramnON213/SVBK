#include <iostream>
using namespace std;

void sum2(int * array, int numEls, int &result)
{
    // TODO
    result = 0;
    for (int i = 0; i < numEls; i++) {
        result += array[i];
    }
}

int main(int narg, char** argv)
{
    int array[3] = {1, 2, 3};
    int result;
    sum2(array, 3, result);
    cout << result;
    return 0;
}