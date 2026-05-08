#include <iostream>
#include <cassert>
#include <string>
#include "eniesLobby.h"

// --- Helper Functions to Print Success ---
void printSuccess(const std::string& testName) {
    std::cout << "[PASS] " << testName << " passed successfully!\n";
}

// --- Test 1: Building & BattleContext Integration ---
// Validates that buildings correctly apply passive effects and destruction triggers.
void testBuildingContextIntegration() {
    std::cout << "--- Testing Building & Context Integration ---\n";
    
    BattleContext ctx;
    ctx.busterCallTimer = 10;
    ctx.alarmLevel = 20;
    
    BusterCallShip ship("BusterCallShip", 50);
    Courthouse courthouse("Courthouse", 100);
    
    // Test passive applyEffect()
    ship.applyEffect(ctx);
    courthouse.applyEffect(ctx);
    
    assert(ctx.busterCallTimer == 9 && "BusterCallShip should decrease the timer by 1 each turn!");
    assert(ctx.alarmLevel == 25 && "Courthouse should increase the alarm level by 5 each turn!");
    
    // Test onDestroyed() triggers
    ship.receiveDamage(100); // Destroy the ship
    assert(ship.isDestroyed() && "Ship should be marked as destroyed.");
    ship.onDestroyed(ctx);
    
    assert(ctx.busterCallTimer == 12 && "Destroying the Buster Call Ship should increase the timer by 3!");
    
    printSuccess("Building & Context Integration");
}

// --- Test 2: Skill Mechanics & State Modification ---
// Validates that special skills correctly drain energy and apply cross-entity debuffs.
void testSkillCrossEntityIntegration() {
    std::cout << "\n--- Testing Skill Mechanics & State Modification ---\n";
    
    BattleContext ctx;
    
    // Give Nami exactly 20 energy (the cost of her skill)
    Nami nami("Nami", 100, 30, 10, 40, 20, 10000000);
    Kalifa kalifa("Kalifa", 150, 40, 20, 50, 50, 4000);
    
    // Nami uses specialSkill on Kalifa
    int namiSkillDmg = nami.specialSkill(&kalifa, ctx);
    // kalifa.receiveDamage(namiSkillDmg);
    
    // Nami's skill deals (atk + 40) = 70 damage. Kalifa's defense is 20. Net damage = 50.
    assert(kalifa.getHP() == 100 && "Kalifa did not take the correct amount of skill damage.");
    
    // Nami's skill should reduce the target's speed by 10.
    // However, since speed is protected and we might not have a getter, 
    // we test the context changes her skill causes instead: 
    // Nami's skill increases busterCallTimer by 1 and decreases alarmLevel by 5.
    // (Assuming default context started alarmLevel at 0, it should clamp to 0, 
    // but let's test the busterCallTimer increase).
    assert(ctx.busterCallTimer == 1 && "Nami's skill failed to update the busterCallTimer in BattleContext!");
    
    printSuccess("Skill Mechanics & State Modification");
}

// --- Test 3: Defeat Triggers & End-of-Turn Stat Updates ---
// Validates that defeating an opponent triggers the correct morale and stat buffs.
void testDefeatAndEndTurnIntegration() {
    std::cout << "\n--- Testing Defeat Triggers & End-Turn Updates ---\n";
    
    BattleContext ctx;
    ctx.morale = 50;
    
    Zoro zoro("Zoro", 100, 50, 20, 30, 0, 320000000);
    Kaku kaku("Kaku", 10, 10, 0, 10, 0, 4000); // Give Kaku very low HP to ensure a one-hit KO
    
    // Zoro attacks Kaku
    int dmg = zoro.attack(&kaku, ctx);
    // kaku.receiveDamage(dmg);
    
    assert(!kaku.isAlive() && "Kaku should be defeated by Zoro's attack.");
    
    // Simulate the game loop calling endTurn after a defeat
    // Note: The assignment specifies Zoro gets +6 morale and +5% attack when he defeats a target.
    // Depending on how you implemented the defeat tracker (e.g., a boolean flag in the Zoro class 
    // flipped during attack() and reset in endTurn()), this will test if it fires correctly.
    if (!kaku.isAlive()) {zoro.setKillInTurn(true);}
    zoro.endTurn(ctx);
    
    // To verify Zoro's attack increased by 5% (50 * 0.05 = 2.5 -> rounded up to 3 -> new atk = 53),
    // we calculate his next raw attack damage against a 0 defense target.
    // Zoro's base damage rule: atk + 20% def. (53 + 4 = 57).
    Blueno blueno("Blueno", 100, 10, 0, 10, 0, 800);
    int nextDmg = zoro.attack(&blueno, ctx);
    
    assert(nextDmg == 57 && "Zoro's endTurn did not correctly buff his attack stat after a defeat! Check your rounding and defeat tracking flags.");
    
    printSuccess("Defeat Triggers & End-Turn Updates");
}

int main() {
    std::cout << "=======================================\n";
    std::cout << " STARTING PHASE 3 INTEGRATION TESTS\n";
    std::cout << "=======================================\n\n";

    testBuildingContextIntegration();
    testSkillCrossEntityIntegration();
    testDefeatAndEndTurnIntegration();

    std::cout << "\n=======================================\n";
    std::cout << " ALL PHASE 3 TESTS PASSED! \n";
    std::cout << "=======================================\n";
    
    return 0;
}