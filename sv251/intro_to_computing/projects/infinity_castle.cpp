#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int slayerLevel, hp, hasTalisman, demonPresence, demonRank, allyCount, bossHP, totalDamage, specialMoveReady, finalHP;
    double breathingMastery, swordSharpness, power, adv;
    char timeOfDay;

    cin >> slayerLevel >> hp >> breathingMastery >> hasTalisman >> timeOfDay >> demonPresence >> demonRank >> swordSharpness >> allyCount >> bossHP >> totalDamage >> specialMoveReady;

    cout << "[Scene 1] Rank: ";
    power = slayerLevel*10 + hp/10 + breathingMastery*50;
    if (power >= 120) cout << "Hashira";
    else if (power >= 80) cout << "Elite";
    else cout << "Novice";
    cout << " (power = " << setprecision(1) << fixed << power << ")" << endl;

    cout << "[Scene 2] ";
    if (hasTalisman == 0)   cout << "Denied: No talisman.";
    else if (timeOfDay != 'D' && timeOfDay != 'N')  cout << "Warning: invalid timeOfDay.";
    else if (timeOfDay == 'N' && demonPresence == 1) cout << "Open silently.";
    else cout << "Open cautiously.";
    cout << endl;

    cout << "[Scene 3] ";
    adv = (101 - demonRank*15) + swordSharpness*0.4 + allyCount*5;
    if (adv >= 100) cout << "Engage head-on";
    else if (adv >= 60) cout << "Harass and probe";
    else cout << "Retreat and regroup";
    cout << " (adv = " << setprecision(1) << fixed << adv << ")" << endl;

    cout << "[Scene 4] ";
    finalHP = bossHP - totalDamage;
    if (finalHP <= 0)   cout << "Boss defeated!";
    else if (specialMoveReady == 1 && finalHP <= 50)    cout << "Use special move to finish!";
    else cout << "Withdraw to heal.";
    if (finalHP < 0)    finalHP = 0;
    cout << " (finalHP = " << finalHP << ")" << endl;

}