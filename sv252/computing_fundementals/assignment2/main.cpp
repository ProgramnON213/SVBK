
#include "eniesLobby.h"

using namespace std;

int main(int argc, const char * argv[]) {
    EniesLobbyBattle battle = EniesLobbyBattle(argv[1]);
    battle.tempLog();
    battle.runBattle();
    cout << battle.getResult();

    return 0;
}
