#include <gtest/gtest.h>
#include <memory>
#include "../HeaderFiles/ComponentFactory.h"
#include "../HeaderFiles/ComponentSpec.h"
#include "../HeaderFiles/Cargo/Cargo.h"
#include "../HeaderFiles/Engine/Engine.h"
#include "../HeaderFiles/Shield/Shield.h"
#include "../HeaderFiles/Weapon/Weapon.h"

class ComponentFactoryTests : public ::testing::Test {
protected:
    void SetUp() override {
        ComponentCatalog::GetInstance().LoadFromJSON("components.json");
    }
};

TEST_F(ComponentFactoryTests, CreateCargoFromJSON) {
    Cargo oxygen = ComponentFactory::CreateCargoByID("oxygen");
    EXPECT_EQ(oxygen.GetName(), "Oxygen");
    EXPECT_EQ(oxygen.GetAtomicNumber(), 8);
    EXPECT_EQ(oxygen.GetPrice(), 5000);
    EXPECT_EQ(oxygen.GetStateAt20(), "Gas");
}

TEST_F(ComponentFactoryTests, CreateEngineFromJSON) {
    Engine engine = ComponentFactory::CreateEngineByID("nomad_f1g_elipsion");
    EXPECT_EQ(engine.GetName(), "Nomad F1G Elipsion Engine");
    EXPECT_EQ(engine.GetPowerUsage(), 115);
    EXPECT_EQ(engine.GetRadiationLevel(), 2);
    EXPECT_EQ(engine.GetPrice(), 15000);
}

TEST_F(ComponentFactoryTests, CreateShieldFromJSON) {
    Shield shield = ComponentFactory::CreateShieldByID("sgd2_advance_protector_fighter");
    EXPECT_EQ(shield.GetName(), "SGD2 Advance Protector Fighter Shield");
    EXPECT_EQ(shield.GetCapacity(), 8500);
    EXPECT_EQ(shield.GetRegenDelay(), 10);
    EXPECT_EQ(shield.GetArmorRating(), 450);
    EXPECT_EQ(shield.GetPrice(), 20000);
}

TEST_F(ComponentFactoryTests, CreateWeaponFromJSON) {
    Weapon weapon = ComponentFactory::CreateWeaponByID("h4z_brimstone_helfire_turret");
    EXPECT_EQ(weapon.GetName(), "H4Z Brimstone Helfire Turret");
    EXPECT_EQ(weapon.GetRotation(), 360);
    EXPECT_EQ(weapon.GetDamage(), 625);
    EXPECT_DOUBLE_EQ(weapon.GetLifeTime(), 3.75);
    EXPECT_EQ(weapon.GetPrice(), 52000);
}

TEST_F(ComponentFactoryTests, CreateAllCargo) {
    std::vector<Cargo> all_cargo = ComponentFactory::CreateAllCargo();
    EXPECT_EQ(all_cargo.size(), 3);
}

TEST_F(ComponentFactoryTests, CreateAllEngines) {
    std::vector<Engine> all_engines = ComponentFactory::CreateAllEngines();
    EXPECT_EQ(all_engines.size(), 3);
}

TEST_F(ComponentFactoryTests, CreateAllShields) {
    std::vector<Shield> all_shields = ComponentFactory::CreateAllShields();
    EXPECT_EQ(all_shields.size(), 3);
}

TEST_F(ComponentFactoryTests, CreateAllWeapons) {
    std::vector<Weapon> all_weapons = ComponentFactory::CreateAllWeapons();
    EXPECT_EQ(all_weapons.size(), 3);
}

TEST_F(ComponentFactoryTests, CreateByName) {
    Cargo cargo = ComponentFactory::CreateCargoByName("Radon");
    EXPECT_EQ(cargo.GetName(), "Radon");
    EXPECT_EQ(cargo.GetAtomicNumber(), 86);
}

TEST_F(ComponentFactoryTests, InvalidIDReturnsDefault) {
    Cargo cargo = ComponentFactory::CreateCargoByID("invalid_id");
    EXPECT_EQ(cargo.GetName(), "");
}
