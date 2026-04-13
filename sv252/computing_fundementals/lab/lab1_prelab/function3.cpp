#include <iostream>
using namespace std;

bool completeNum(int N)
{
    return ((N==6) || (N==28) || (N==496) || (N==8128) || (N==33550336));
}

int main(int narg, char** argv)
{
    cout << completeNum(6);
}