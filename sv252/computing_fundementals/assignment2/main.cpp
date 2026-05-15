
#include "eniesLobby.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Character* strawHats[3];
    strawHats[0] = new Luffy("Luffy", 120, 35, 20, 25, 50, 1500000000LL);
    strawHats[1] = new Nami("Nami", 80, 22, 12, 35, 60, 366000000LL);
    strawHats[2] = new Franky("Franky", 130, 32, 28, 18, 50, 394000000LL);

    Character* cp9[3];
    cp9[0] = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    cp9[1] = new Kaku("Kaku", 130, 35, 22, 28, 55, 2200);
    cp9[2] = new Kalifa("Kalifa", 95, 26, 18, 32, 50, 630);

    BattleContext context;
    strawHats[0]->specialSkill(cp9[0], context);
    cout << cp9[0]->str() << endl;

    for (int i = 0; i < 3; i++) delete strawHats[i];
    for (int i = 0; i < 3; i++) delete cp9[i];
    cout << "Closing main" << endl;
    return 0;
}
