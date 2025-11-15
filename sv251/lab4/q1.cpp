#include <iostream>
#include <string>
using namespace std;

int distance(string moves);

int main() {
    cout << distance("_______");
    return 0;
}

int distance(string moves) {
    int l_count = 0, r_count = 0, free_count = 0, ans;
    for (size_t i = 0; i < moves.length(); i++) {
        if (moves[i] == 'L') l_count += 1;
        else if (moves[i] == 'R')   r_count += 1;
        else  free_count += 1;
    }
    ans = l_count - r_count;
    if (ans < 0)    ans = -ans;
    return ans += free_count;
}