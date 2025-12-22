#include <iostream>
#include <cassert>
#include <stdexcept>
#include "HeaderFiles/Ships/Ship.h"
#include "HeaderFiles/ComponentFactory.h"
#include "HeaderFiles/Ships/ShipSpec.h"

// Simple test to verify our fixes
int main() {
    std::cout << "Testing high-priority fixes...\n\n";

    // Test 1: const& string parameters (compile-time check - if this compiles, it works)
    std::cout << "[TEST 1] const& string parameters - ";
    const std::string faction = "TestFaction";
    SpaceShip ship1(faction);
    SpaceShip ship2(faction, 1000);
    std::cout << "PASSED (compiles correctly)\n";

    // Test 2: RemoveCargo bug fix (front/back mismatch)
    std::cout << "[TEST 2] RemoveCargo bug fix - ";
    SpaceShip ship3;
    Cargo cargo1("Oxygen", "Test", 100, 8, 16.0, "Gas");
    Cargo cargo2("Helium", "Test", 200, 2, 4.0, "Gas");
    Cargo cargo3("Neon", "Test", 300, 10, 20.0, "Gas");

    ship3.AddCargo(cargo1);  // Add 100
    ship3.AddCargo(cargo2);  // Add 200
    ship3.AddCargo(cargo3);  // Add 300
    int64_t price_with_all = ship3.GetShipPrice();  // Should be 600

    ship3.RemoveCargo();  // Should remove cargo3 (300) - the last one added
    int64_t price_after_remove = ship3.GetShipPrice();  // Should be 300

    if (price_with_all == 600 && price_after_remove == 300) {
        std::cout << "PASSED (correct price: " << price_after_remove << ")\n";
    } else {
        std::cout << "FAILED (expected 300, got " << price_after_remove << ")\n";
        return 1;
    }

    // Test 3: RemoveShield bug fix (same issue)
    std::cout << "[TEST 3] RemoveShield bug fix - ";
    SpaceShip ship4;
    Shield shield1("Shield1", "Test", 500, 100, 1000, 2000, 5, 50, 10);
    Shield shield2("Shield2", "Test", 800, 150, 1500, 2500, 6, 60, 12);

    ship4.AddShield(shield1);  // Add 500
    ship4.AddShield(shield2);  // Add 800
    int64_t shield_price_all = ship4.GetShipPrice();  // Should be 1300

    ship4.RemoveShield();  // Should remove shield2 (800) - the last one
    int64_t shield_price_after = ship4.GetShipPrice();  // Should be 500

    if (shield_price_all == 1300 && shield_price_after == 500) {
        std::cout << "PASSED (correct price: " << shield_price_after << ")\n";
    } else {
        std::cout << "FAILED (expected 500, got " << shield_price_after << ")\n";
        return 1;
    }

    // Test 4: Error handling (exceptions instead of cout)
    std::cout << "[TEST 4] Exception handling - ";
    SpaceShip ship5;
    bool exception_thrown = false;

    try {
        ship5.RemoveCargo();  // Should throw exception
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
        // std::cout << "Caught expected exception: " << e.what() << "\n";
    }

    if (exception_thrown) {
        std::cout << "PASSED (exception thrown correctly)\n";
    } else {
        std::cout << "FAILED (no exception thrown)\n";
        return 1;
    }

    // Test 5: Counter removal (engines)
    std::cout << "[TEST 5] Engine counter fix - ";
    SpaceShip ship6;
    Engine engine1("Engine1", "Test", 1000, 100, 1);
    Engine engine2("Engine2", "Test", 2000, 150, 2);
    Engine engine3("Engine3", "Test", 3000, 200, 3);

    ship6.AddEngine(engine1);  // 1000
    ship6.AddEngine(engine2);  // 2000
    ship6.AddEngine(engine3);  // 3000
    int64_t engine_total = ship6.GetShipPrice();  // 6000

    ship6.RemoveEngine();  // Remove last (3000)
    int64_t after_one = ship6.GetShipPrice();  // 3000

    ship6.RemoveEngine();  // Remove last (2000)
    int64_t after_two = ship6.GetShipPrice();  // 1000

    if (engine_total == 6000 && after_one == 3000 && after_two == 1000) {
        std::cout << "PASSED (prices: " << engine_total << " -> " << after_one << " -> " << after_two << ")\n";
    } else {
        std::cout << "FAILED (expected 6000->3000->1000, got "
                  << engine_total << "->" << after_one << "->" << after_two << ")\n";
        return 1;
    }

    // Test 6: Weapon counter fix
    std::cout << "[TEST 6] Weapon counter fix - ";
    SpaceShip ship7;
    Weapon weapon1("Weapon1", "Test", 500, 360, 2.0, 1000, 300, 100);
    Weapon weapon2("Weapon2", "Test", 700, 360, 2.5, 1200, 350, 120);

    ship7.AddWeapon(weapon1);  // 500
    ship7.AddWeapon(weapon2);  // 700
    int64_t weapon_total = ship7.GetShipPrice();  // 1200

    ship7.RemoveWeapon();  // Remove last (700)
    int64_t weapon_after = ship7.GetShipPrice();  // 500

    if (weapon_total == 1200 && weapon_after == 500) {
        std::cout << "PASSED (correct price: " << weapon_after << ")\n";
    } else {
        std::cout << "FAILED (expected 500, got " << weapon_after << ")\n";
        return 1;
    }

    std::cout << "\n=== ALL TESTS PASSED ===\n";
    return 0;
}
