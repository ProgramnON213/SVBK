#include <iostream>
#include <cassert>
#include <string>
#include "eniesLobby.h"

// --- Helper Functions to Print Success ---
void printSuccess(const std::string& testName) {
    std::cout << "[PASS] " << testName << " passed successfully!\n";
}

// --- Test 1: String Formatting ---
// Validates that the str() methods output the exact required formats.
void testStringFormatting() {
    std::cout << "--- Testing String Formatting ---\n";
    
    // Test StrawHat format [cite: 131]
    Luffy luffy("Luffy", 120, 35, 20, 25, 50, 150000000);
    std::string expectedLuffy = "StrawHat [name=Luffy, hp=120, atk=35, def=20, speed=25, energy=50, bounty=150000000]";
    assert(luffy.str() == expectedLuffy && "Luffy str() format is incorrect! Check commas and spacing.");

    // Test CP9Agent format [cite: 259]
    Lucci lucci("Lucci", 150, 40, 25, 30, 60, 4000);    
    std::string expectedLucci = "CP9 [name=Lucci, hp=150, atk=40, def=25, speed=30, energy=60, doriki=4000]";
    assert(lucci.str() == expectedLucci && "Lucci str() format is incorrect! Check commas and spacing.");

    // Test Building format [cite: 406, 408]
    MainGate gate("MainGate", 200);
    std::string expectedGate = "Building [name=MainGate, hp=200, maxHP=200, destroyed=false]";
    assert(gate.str() == expectedGate && "MainGate str() format is incorrect! Ensure 'destroyed' prints as true/false.");

    printSuccess("String Formatting");
}

// --- Test 2: Stat Clamping ---
// Validates that HP and destroyed states do not exceed boundaries.
void testClamping() {
    std::cout << "\n--- Testing Stat Clamping ---\n";
    
    Luffy luffy("Luffy", 100, 30, 10, 20, 50, 1000);
    
    // Attack deals 200 damage. Luffy has 10 defense. He takes 190 damage.
    // HP must clamp to 0, and he should not be alive[cite: 89, 90].
    luffy.receiveDamage(200); 
    assert(luffy.getHP() == 0 && "Character HP should not drop below 0!");
    assert(!luffy.isAlive() && "Character should be dead (alive=false) when HP hits 0!");

    // Building HP clamping [cite: 396]
    MainGate gate("MainGate", 50);
    gate.receiveDamage(100);
    assert(gate.isDestroyed() && "Gate should be marked as destroyed (true)!");

    printSuccess("Stat Clamping");
}

// --- Test 3: Mathematical Rounding ---
// Validates that computed values round UP to the nearest integer.
void testRounding() {
    std::cout << "\n--- Testing Mathematical Rounding ---\n";
    
    // Setup BattleContext for the attack method signature
    BattleContext ctx;

    // Sanji's attack damage: atk + 50% of speed[cite: 172].
    // Give Sanji an odd speed of 25. 50% of 25 = 12.5. 
    // Assignment rule: Always round UP[cite: 39]. So 12.5 -> 13.
    // Total attack: 20 (atk) + 13 (speed bonus) = 33.
    Sanji sanji("Sanji", 100, 20, 10, 25, 50, 1000);
    
    // Give target 0 defense so we can measure raw damage easily.
    Lucci target("Lucci", 100, 10, 0, 10, 50, 1000); 
    
    int actualDamageDealt = sanji.attack(&target, ctx);
    
    // Assert rounding up worked
    assert(actualDamageDealt == 33 && "Mathematical rounding failed! Ensure you are rounding UP (e.g., using ceil()).");
    
    printSuccess("Mathematical Rounding");
}

int main() {
    std::cout << "=======================================\n";
    std::cout << " STARTING PHASE 2 UNIT TESTS\n";
    std::cout << "=======================================\n\n";

    testStringFormatting();
    testClamping();
    testRounding();

    std::cout << "\n=======================================\n";
    std::cout << " ALL PHASE 2 TESTS PASSED! \n";
    std::cout << "=======================================\n";
    
    return 0;
}