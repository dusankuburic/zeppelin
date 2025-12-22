#include <gtest/gtest.h>
#include <memory>
#include "../HeaderFiles/Cargo/Cargo.h"
#include "../HeaderFiles/Engine/Engine.h"
#include "../HeaderFiles/Shield/Shield.h"
#include "../HeaderFiles/Weapon/Weapon.h"
#include "../SourceFiles/PRICE.h"

class CargoTests : public ::testing::Test {
protected:
    void SetUp() override {
        test_cargo = std::make_unique<Cargo>(
            "TestCargo",
            "TestFaction",
            500
        );
    }

    std::unique_ptr<Cargo> test_cargo;
};

TEST_F(CargoTests, DefaultConstructor) {
    Cargo cargo;
    EXPECT_EQ(cargo.GetCargoName(), "");
    EXPECT_EQ(cargo.GetFactionName(), "");
    EXPECT_EQ(cargo.GetCargoPrice(), 0);
}

TEST_F(CargoTests, ParameterizedConstructor) {
    EXPECT_EQ(test_cargo->GetCargoName(), "TestCargo");
    EXPECT_EQ(test_cargo->GetFactionName(), "TestFaction");
    EXPECT_EQ(test_cargo->GetCargoPrice(), 500);
}

TEST_F(CargoTests, SetAndGetName) {
    test_cargo->SetName("NewCargo");
    EXPECT_EQ(test_cargo->GetCargoName(), "NewCargo");
}

TEST_F(CargoTests, SetAndGetFactionName) {
    test_cargo->SetFactionName("NewFaction");
    EXPECT_EQ(test_cargo->GetFactionName(), "NewFaction");
}

TEST_F(CargoTests, PriceIsInitializedToZero) {
    Cargo new_cargo;
    EXPECT_EQ(new_cargo.GetCargoPrice(), 0);
}

TEST_F(CargoTests, CanHandleInt64PriceRange) {
    int64_t large_price = 9223372036854775807LL;
    Cargo large_cargo("ExpensiveCargo", "Faction", large_price);
    EXPECT_EQ(large_cargo.GetCargoPrice(), large_price);
}

class EngineTests : public ::testing::Test {
protected:
    void SetUp() override {
        test_engine = std::make_unique<Engine>(
            "TestEngine",
            "TestFaction",
            5000
        );
    }

    std::unique_ptr<Engine> test_engine;
};

TEST_F(EngineTests, DefaultConstructor) {
    Engine engine;
    EXPECT_EQ(engine.GetEngineName(), "");
    EXPECT_EQ(engine.GetFactionName(), "");
    EXPECT_EQ(engine.GetEnginePrice(), 0);
}

TEST_F(EngineTests, ParameterizedConstructor) {
    EXPECT_EQ(test_engine->GetEngineName(), "TestEngine");
    EXPECT_EQ(test_engine->GetFactionName(), "TestFaction");
    EXPECT_EQ(test_engine->GetEnginePrice(), 5000);
}

TEST_F(EngineTests, SetAndGetName) {
    test_engine->SetName("NewEngine");
    EXPECT_EQ(test_engine->GetEngineName(), "NewEngine");
}

TEST_F(EngineTests, SetAndGetFactionName) {
    test_engine->SetFactionName("NewFaction");
    EXPECT_EQ(test_engine->GetFactionName(), "NewFaction");
}

TEST_F(EngineTests, PriceIsInitializedToZero) {
    Engine new_engine;
    EXPECT_EQ(new_engine.GetEnginePrice(), 0);
}

class ShieldTests : public ::testing::Test {
protected:
    void SetUp() override {
        test_shield = std::make_unique<Shield>(
            "TestShield",
            "TestFaction",
            8000
        );
    }

    std::unique_ptr<Shield> test_shield;
};

TEST_F(ShieldTests, DefaultConstructor) {
    Shield shield;
    EXPECT_EQ(shield.GetShieldName(), "");
    EXPECT_EQ(shield.GetFactionName(), "");
    EXPECT_EQ(shield.GetShieldPrice(), 0);
}

TEST_F(ShieldTests, ParameterizedConstructor) {
    EXPECT_EQ(test_shield->GetShieldName(), "TestShield");
    EXPECT_EQ(test_shield->GetFactionName(), "TestFaction");
    EXPECT_EQ(test_shield->GetShieldPrice(), 8000);
}

TEST_F(ShieldTests, SetAndGetName) {
    test_shield->SetName("NewShield");
    EXPECT_EQ(test_shield->GetShieldName(), "NewShield");
}

TEST_F(ShieldTests, SetAndGetFactionName) {
    test_shield->SetFactionName("NewFaction");
    EXPECT_EQ(test_shield->GetFactionName(), "NewFaction");
}

TEST_F(ShieldTests, PriceIsInitializedToZero) {
    Shield new_shield;
    EXPECT_EQ(new_shield.GetShieldPrice(), 0);
}

class WeaponTests : public ::testing::Test {
protected:
    void SetUp() override {
        test_weapon = std::make_unique<Weapon>(
            "TestWeapon",
            "TestFaction",
            6000
        );
    }

    std::unique_ptr<Weapon> test_weapon;
};

TEST_F(WeaponTests, DefaultConstructor) {
    Weapon weapon;
    EXPECT_EQ(weapon.GetWeaponName(), "");
    EXPECT_EQ(weapon.GetFactionName(), "");
    EXPECT_EQ(weapon.GetWeaponPrice(), 0);
}

TEST_F(WeaponTests, ParameterizedConstructor) {
    EXPECT_EQ(test_weapon->GetWeaponName(), "TestWeapon");
    EXPECT_EQ(test_weapon->GetFactionName(), "TestFaction");
    EXPECT_EQ(test_weapon->GetWeaponPrice(), 6000);
}

TEST_F(WeaponTests, SetAndGetName) {
    test_weapon->SetName("NewWeapon");
    EXPECT_EQ(test_weapon->GetWeaponName(), "NewWeapon");
}

TEST_F(WeaponTests, SetAndGetFactionName) {
    test_weapon->SetFactionName("NewFaction");
    EXPECT_EQ(test_weapon->GetFactionName(), "NewFaction");
}

TEST_F(WeaponTests, PriceIsInitializedToZero) {
    Weapon new_weapon;
    EXPECT_EQ(new_weapon.GetWeaponPrice(), 0);
}

class SecurityTests : public ::testing::Test {};

TEST_F(SecurityTests, CargoInitializedVariablesNeverRandom) {
    Cargo cargo1;
    Cargo cargo2;
    Cargo cargo3;

    EXPECT_EQ(cargo1.GetCargoPrice(), 0);
    EXPECT_EQ(cargo2.GetCargoPrice(), 0);
    EXPECT_EQ(cargo3.GetCargoPrice(), 0);
}

TEST_F(SecurityTests, EngineInt64PreventsPriceOverflow) {
    int64_t large_price = 2147483647LL;
    Engine engine("Test", "Faction", large_price);
    EXPECT_EQ(engine.GetEnginePrice(), large_price);
}

TEST_F(SecurityTests, WeaponCanHoldExtremelyLargePrices) {
    int64_t extreme_price = 9223372036854775000LL;
    Weapon weapon("Test", "Faction", extreme_price);
    EXPECT_EQ(weapon.GetWeaponPrice(), extreme_price);
}

TEST_F(SecurityTests, AllComponentsUseConsistentPricingType) {
    int64_t price = 50000;

    Cargo cargo("C", "F", price);
    Engine engine("E", "F", price);
    Shield shield("S", "F", price);
    Weapon weapon("W", "F", price);

    EXPECT_EQ(cargo.GetCargoPrice(), price);
    EXPECT_EQ(engine.GetEnginePrice(), price);
    EXPECT_EQ(shield.GetShieldPrice(), price);
    EXPECT_EQ(weapon.GetWeaponPrice(), price);
}
