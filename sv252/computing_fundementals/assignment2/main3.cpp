#include <iostream>
#include <string>
#include "eniesLobby.h"

int main() {
    std::cout << "=======================================\n";
    std::cout << " STARTING PHASE 4: FULL BATTLE SIMULATION\n";
    std::cout << "=======================================\n\n";

    // 1. Initialize the battle with your test file
    std::cout << "[LOG] Loading battlefield data from test_input.txt...\n";
    EniesLobbyBattle battle("test_input.txt");

    // 2. Run the game loop
    std::cout << "[LOG] Commencing the battle...\n";
    battle.runBattle();

    // 3. Output the final state
    std::cout << "\n[LOG] Battle has concluded!\n";
    std::string finalResult = battle.getResult();
    
    std::cout << "---------------------------------------\n";
    std::cout << " FINAL RESULT STRING:\n";
    std::cout << " " << finalResult << "\n";
    std::cout << "---------------------------------------\n";

    // Expected format: resultCode turnCount morale alarmLevel rescueProgress escapeProgress busterCallTimer
    // e.g., STRAW_HAT_WIN 12 60 10 100 100 8

    std::cout << "\n=======================================\n";
    std::cout << " SIMULATION COMPLETE. CHECK VALGRIND FOR LEAKS! \n";
    std::cout << "=======================================\n";

    return 0;
}