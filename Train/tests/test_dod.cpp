#include <iostream>
#include <cassert>
#include <string>
#include "Context.hpp"
#include "Systems.hpp"

// Test framework helpers
int test_count = 0;
int test_passed = 0;

#define TEST(name) \
    void test_##name(); \
    void run_test_##name() { \
        test_count++; \
        std::cout << "Running test: " << #name << "... "; \
        try { \
            test_##name(); \
            test_passed++; \
            std::cout << "PASSED\n"; \
        } catch (const std::exception& e) { \
            std::cout << "FAILED: " << e.what() << "\n"; \
        } catch (...) { \
            std::cout << "FAILED: Unknown exception\n"; \
        } \
    } \
    void test_##name()

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        throw std::runtime_error(std::string("Assertion failed: ") + #expr); \
    }

#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        throw std::runtime_error(std::string("Assertion failed: ") + #a + " != " + #b); \
    }

#define ASSERT_NEAR(a, b, epsilon) \
    if (std::abs((a) - (b)) > (epsilon)) { \
        throw std::runtime_error(std::string("Assertion failed: ") + #a + " not near " + #b); \
    }

// Factory functions
CargoID CreateCargo(Context& ctx, std::string name, float weight, float price) {
    CargoID id = static_cast<CargoID>(ctx.cargos.weights.size());
    ctx.cargos.weights.push_back(weight);
    ctx.cargos.prices.push_back(price);
    ctx.cargos.types.push_back(0);
    ctx.cargos.names.push_back(std::move(name));
    return id;
}

WagonID CreateWagon(Context& ctx, float maxW, int maxS) {
    WagonID id = static_cast<WagonID>(ctx.wagons.max_weights.size());
    ctx.wagons.max_weights.push_back(maxW);
    ctx.wagons.current_weights.push_back(0.0f);
    ctx.wagons.max_space.push_back(maxS);
    ctx.wagons.cargo_ids.emplace_back();
    return id;
}

TrainID CreateTrain(Context& ctx, std::string name) {
    TrainID id = static_cast<TrainID>(ctx.trains.names.size());
    ctx.trains.names.push_back(std::move(name));
    ctx.trains.wagon_ids.emplace_back();
    ctx.trains.positions.push_back(0.0f);
    ctx.trains.velocities.push_back(0.0f);
    return id;
}

// ==================== Tests ====================

TEST(cargo_creation) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);

    ASSERT_EQ(c1, 0);
    ASSERT_EQ(ctx.cargos.size(), 1);
    ASSERT_NEAR(ctx.cargos.weights[c1], 100.0f, 0.001f);
    ASSERT_NEAR(ctx.cargos.prices[c1], 50.0f, 0.001f);
    ASSERT_EQ(ctx.cargos.names[c1], "Wood");
}

TEST(multiple_cargo_creation) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    CargoID c3 = CreateCargo(ctx, "Steel", 200.0f, 150.0f);

    ASSERT_EQ(ctx.cargos.size(), 3);
    ASSERT_EQ(c1, 0);
    ASSERT_EQ(c2, 1);
    ASSERT_EQ(c3, 2);
}

TEST(cargo_validation) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);

    ASSERT_TRUE(Systems::ValidateCargoID(ctx, c1));
    ASSERT_TRUE(Systems::ValidateCargoID(ctx, 0));
    ASSERT_TRUE(!Systems::ValidateCargoID(ctx, 1));
    ASSERT_TRUE(!Systems::ValidateCargoID(ctx, -1));
    ASSERT_TRUE(!Systems::ValidateCargoID(ctx, 999));
}

TEST(wagon_creation) {
    Context ctx;
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    ASSERT_EQ(w1, 0);
    ASSERT_EQ(ctx.wagons.size(), 1);
    ASSERT_NEAR(ctx.wagons.max_weights[w1], 5000.0f, 0.001f);
    ASSERT_EQ(ctx.wagons.max_space[w1], 30);
    ASSERT_NEAR(ctx.wagons.current_weights[w1], 0.0f, 0.001f);
}

TEST(wagon_validation) {
    Context ctx;
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    ASSERT_TRUE(Systems::ValidateWagonID(ctx, w1));
    ASSERT_TRUE(Systems::ValidateWagonID(ctx, 0));
    ASSERT_TRUE(!Systems::ValidateWagonID(ctx, 1));
    ASSERT_TRUE(!Systems::ValidateWagonID(ctx, -1));
}

TEST(train_creation) {
    Context ctx;
    TrainID t1 = CreateTrain(ctx, "Express");

    ASSERT_EQ(t1, 0);
    ASSERT_EQ(ctx.trains.size(), 1);
    ASSERT_EQ(ctx.trains.names[t1], "Express");
    ASSERT_NEAR(ctx.trains.positions[t1], 0.0f, 0.001f);
    ASSERT_NEAR(ctx.trains.velocities[t1], 0.0f, 0.001f);
}

TEST(add_cargo_to_wagon) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    bool result = Systems::TryAddCargoToWagon(ctx, w1, c1);

    ASSERT_TRUE(result);
    ASSERT_EQ(ctx.wagons.cargo_ids[w1].size(), 1);
    ASSERT_EQ(ctx.wagons.cargo_ids[w1][0], c1);
    ASSERT_NEAR(ctx.wagons.current_weights[w1], 100.0f, 0.001f);
}

TEST(add_multiple_cargo_to_wagon) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    ASSERT_TRUE(Systems::TryAddCargoToWagon(ctx, w1, c1));
    ASSERT_TRUE(Systems::TryAddCargoToWagon(ctx, w1, c2));

    ASSERT_EQ(ctx.wagons.cargo_ids[w1].size(), 2);
    ASSERT_NEAR(ctx.wagons.current_weights[w1], 120.0f, 0.001f);
}

TEST(wagon_weight_limit) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Heavy", 5000.0f, 100.0f);
    CargoID c2 = CreateCargo(ctx, "Light", 1.0f, 10.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    ASSERT_TRUE(Systems::TryAddCargoToWagon(ctx, w1, c1));
    ASSERT_TRUE(!Systems::TryAddCargoToWagon(ctx, w1, c2));  // Should fail - over weight

    ASSERT_EQ(ctx.wagons.cargo_ids[w1].size(), 1);
}

TEST(wagon_space_limit) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Light", 1.0f, 10.0f);
    WagonID w1 = CreateWagon(ctx, 10000.0f, 2);  // Only 2 spaces

    ASSERT_TRUE(Systems::TryAddCargoToWagon(ctx, w1, c1));
    ASSERT_TRUE(Systems::TryAddCargoToWagon(ctx, w1, c1));
    ASSERT_TRUE(!Systems::TryAddCargoToWagon(ctx, w1, c1));  // Should fail - no space

    ASSERT_EQ(ctx.wagons.cargo_ids[w1].size(), 2);
}

TEST(wagon_value_calculation) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w1, c2);

    double value = Systems::GetWagonValue(ctx, w1);
    ASSERT_NEAR(value, 550.0, 0.001);
}

TEST(train_value_calculation) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);
    WagonID w2 = CreateWagon(ctx, 5000.0f, 30);
    TrainID t1 = CreateTrain(ctx, "Express");

    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w2, c2);

    ctx.trains.wagon_ids[t1].push_back(w1);
    ctx.trains.wagon_ids[t1].push_back(w2);

    double value = Systems::GetTrainValue(ctx, t1);
    ASSERT_NEAR(value, 550.0, 0.001);
}

TEST(total_loaded_cargo_value) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    CargoID c3 = CreateCargo(ctx, "Steel", 200.0f, 150.0f);  // Not loaded
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w1, c2);

    double total = Systems::CalculateTotalLoadedCargoValue(ctx);
    ASSERT_NEAR(total, 550.0, 0.001);  // Only loaded cargo, not c3
}

TEST(movement_update) {
    Context ctx;
    TrainID t1 = CreateTrain(ctx, "Express");
    ctx.trains.velocities[t1] = 10.0f;

    Systems::UpdateMovement(ctx, 1.0f);
    ASSERT_NEAR(ctx.trains.positions[t1], 10.0f, 0.001f);

    Systems::UpdateMovement(ctx, 2.0f);
    ASSERT_NEAR(ctx.trains.positions[t1], 30.0f, 0.001f);
}

TEST(multiple_trains_movement) {
    Context ctx;
    TrainID t1 = CreateTrain(ctx, "Express");
    TrainID t2 = CreateTrain(ctx, "Slow");

    ctx.trains.velocities[t1] = 10.0f;
    ctx.trains.velocities[t2] = 5.0f;

    Systems::UpdateMovement(ctx, 1.0f);

    ASSERT_NEAR(ctx.trains.positions[t1], 10.0f, 0.001f);
    ASSERT_NEAR(ctx.trains.positions[t2], 5.0f, 0.001f);
}

TEST(recalculate_wagon_weights) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);
    CargoID c2 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w1, c2);

    // Manually corrupt the weight
    ctx.wagons.current_weights[w1] = 999.0f;

    // Recalculate should fix it
    Systems::RecalculateAllWagonWeights(ctx);

    ASSERT_NEAR(ctx.wagons.current_weights[w1], 120.0f, 0.001f);
}

TEST(invalid_cargo_id_handling) {
    Context ctx;
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    // Try to add non-existent cargo
    bool result = Systems::TryAddCargoToWagon(ctx, w1, 999);
    ASSERT_TRUE(!result);
}

TEST(invalid_wagon_id_handling) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Wood", 100.0f, 50.0f);

    // Try to add to non-existent wagon
    bool result = Systems::TryAddCargoToWagon(ctx, 999, c1);
    ASSERT_TRUE(!result);
}

TEST(empty_wagon_value) {
    Context ctx;
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    double value = Systems::GetWagonValue(ctx, w1);
    ASSERT_NEAR(value, 0.0, 0.001);
}

TEST(empty_train_value) {
    Context ctx;
    TrainID t1 = CreateTrain(ctx, "Empty");

    double value = Systems::GetTrainValue(ctx, t1);
    ASSERT_NEAR(value, 0.0, 0.001);
}

TEST(duplicate_cargo_instances) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);

    // Add same cargo type multiple times
    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w1, c1);

    ASSERT_EQ(ctx.wagons.cargo_ids[w1].size(), 3);
    ASSERT_NEAR(ctx.wagons.current_weights[w1], 60.0f, 0.001f);

    // Value should count all instances
    double value = Systems::GetWagonValue(ctx, w1);
    ASSERT_NEAR(value, 1500.0, 0.001);  // 3 × 500
}

TEST(loaded_value_unique_cargo) {
    Context ctx;
    CargoID c1 = CreateCargo(ctx, "Gold", 20.0f, 500.0f);
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);
    WagonID w2 = CreateWagon(ctx, 5000.0f, 30);

    // Add same cargo ID to different wagons
    Systems::TryAddCargoToWagon(ctx, w1, c1);
    Systems::TryAddCargoToWagon(ctx, w2, c1);

    // Total loaded value should count unique cargo only once
    double total = Systems::CalculateTotalLoadedCargoValue(ctx);
    ASSERT_NEAR(total, 500.0, 0.001);  // Unique cargo value
}

// ==================== Main Test Runner ====================

int main() {
    std::cout << "=== DOD Train System Test Suite ===\n\n";

    // Run all tests
    run_test_cargo_creation();
    run_test_multiple_cargo_creation();
    run_test_cargo_validation();
    run_test_wagon_creation();
    run_test_wagon_validation();
    run_test_train_creation();
    run_test_add_cargo_to_wagon();
    run_test_add_multiple_cargo_to_wagon();
    run_test_wagon_weight_limit();
    run_test_wagon_space_limit();
    run_test_wagon_value_calculation();
    run_test_train_value_calculation();
    run_test_total_loaded_cargo_value();
    run_test_movement_update();
    run_test_multiple_trains_movement();
    run_test_recalculate_wagon_weights();
    run_test_invalid_cargo_id_handling();
    run_test_invalid_wagon_id_handling();
    run_test_empty_wagon_value();
    run_test_empty_train_value();
    run_test_duplicate_cargo_instances();
    run_test_loaded_value_unique_cargo();

    // Print summary
    std::cout << "\n=== Test Summary ===\n";
    std::cout << "Total tests: " << test_count << "\n";
    std::cout << "Passed: " << test_passed << "\n";
    std::cout << "Failed: " << (test_count - test_passed) << "\n";

    if (test_passed == test_count) {
        std::cout << "\n*** ALL TESTS PASSED ***\n";
        return 0;
    } else {
        std::cout << "\n*** SOME TESTS FAILED ***\n";
        return 1;
    }
}
