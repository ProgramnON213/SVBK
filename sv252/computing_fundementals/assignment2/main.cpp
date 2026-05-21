
#include "eniesLobby.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cout << "Usage: ./main <filename>" << endl;
        return -1;
    }
    // REMINDER: Revisit test5, test8 at morale
    EniesLobbyBattle battle = EniesLobbyBattle(argv[1]);
    battle.runBattle();
    cout << battle.getResult() << endl;
    return 0;
}
