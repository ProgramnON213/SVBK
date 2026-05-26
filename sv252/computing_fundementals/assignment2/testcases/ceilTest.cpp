#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;

// Your implemented helper function
int multiplyStat(int percentage, int damage) {
    return (damage * percentage + 99) / 100;
}

// The "Source of Truth" using standard double arithmetic
int truthCeil(int percentage, int damage) {
    // Epsilon (- 1e-9) handles floating point inaccuracy 
    // Double cast prevents integer division before division by 100
    double rawResult = (double(damage) * double(percentage)) / 100.0;
    return std::ceil(rawResult - 1e-9); 
}

// Test runner macro
#define RUN_TEST(pct, dmg) \
    do { \
        int expected = truthCeil(pct, dmg); \
        int actual = multiplyStat(pct, dmg); \
        if (expected != actual) { \
            cout << "FAIL: " << pct << "% of " << dmg << " | Expected: " << expected << ", Got: " << actual << "\n"; \
        } else { \
            cout << "PASS: " << pct << "% of " << dmg << " -> " << actual << "\n"; \
        } \
        assert(expected == actual); \
    } while(0)

int main() {
    cout << "--- STANDARD MULTIPLIERS ---\n";
    RUN_TEST(120, 10); // Franky's Coup de Vent: exactly 12
    RUN_TEST(150, 15); // 150% of 15 = 22.5 -> ceil to 23
    RUN_TEST(50, 33);  // 50% of 33 = 16.5 -> ceil to 17
    
    cout << "\n--- EXACT BOUNDARIES (The .00, .01, and .99 cases) ---\n";
    RUN_TEST(100, 50); // Exact multiple: 50 * 100 = 5000 / 100 = 50
    RUN_TEST(101, 100); // 100 * 101% = 101.0 -> exactly 101
    RUN_TEST(1, 101);  // 1% of 101 = 1.01 -> ceil to 2
    RUN_TEST(99, 100); // 99% of 100 = 99.0 -> exactly 99
    RUN_TEST(1, 99);   // 1% of 99 = 0.99 -> ceil to 1
    
    cout << "\n--- EXTREME SMALL VALUES (Zeroes and Ones) ---\n";
    RUN_TEST(0, 500);  // 0% of 500 damage = 0
    RUN_TEST(150, 0);  // 150% of 0 damage = 0
    RUN_TEST(0, 0);    // 0% of 0 = 0
    RUN_TEST(1, 1);    // 1% of 1 = 0.01 -> ceil to 1

    cout << "\n--- LARGE VALUES (Stress Testing) ---\n";
    RUN_TEST(250, 9999); 
    RUN_TEST(1000, 8543); 

    cout << "\nALL TESTS PASSED SUCCESSFULLY!\n";
    return 0;
}