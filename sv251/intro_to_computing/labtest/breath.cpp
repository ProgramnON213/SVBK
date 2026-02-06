#include <iostream>
using namespace std;

int computeStamina(string moves, int hp, double breathingMastery);

int main() {
    cout << computeStamina("C", 1000, 1.0) << endl;
    return 0;
}

int computeStamina(string moves, int hp, double breathingMastery) {
    int length = moves.size();
    float left = float(hp);
    for (int i = 0; i < length; i++) {
        if (moves[i] == 'A') left -= (1.0 - breathingMastery);
        else if (moves[i] == 'B') left -= (2.0 - breathingMastery);
        else if (moves[i] == 'C') left -= (3.0 - breathingMastery);
    }
    if (left < 0)   return 0;
    else return int(left);
}