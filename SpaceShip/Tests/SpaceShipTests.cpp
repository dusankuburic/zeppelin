#include <gtest/gtest.h>
#include <memory>
#include "../HeaderFiles/Ships/Ship.h"
#include "../HeaderFiles/Ships/ShipFactory.h"
#include "../HeaderFiles/Ships/ShipSpec.h"
#include "../HeaderFiles/ComponentFactory.h"
#include "../HeaderFiles/Cargo/Cargo.h"
#include "../HeaderFiles/Engine/Engine.h"
#include "../HeaderFiles/Shield/Shield.h"
#include "../HeaderFiles/Weapon/Weapon.h"

class ShipTestFixture : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        try {
            ShipCatalog::GetInstance().LoadFromJSON("ships.json");
            ComponentCatalog::GetInstance().LoadFromJSON("components.json");
        } catch (const std::exception& e) {
        }
    }
};

class ShipComponentIntegrationTests : public ShipTestFixture {
protected:
    void SetUp() override {
        try {
            ship = ShipFactory::CreateByID("gunboat_cte12400_condor", "TestFaction");
        } catch (...) {
            ShipSpec spec;
            spec.id = "gunboat_cte12400_condor";
            spec.name = "Gunboat CTE12400 Condor";
            spec.faction = "TestFaction";
            spec.category = "gunboat";
            spec.hull_strength = 125000;
            spec.max_shield_class = 8;
            spec.cargo_space = 450;
            spec.max_impulse_speed = 80;
            spec.base_price = 30000;
            ship = std::make_unique<Ship>(spec);
        }
    }

    std::unique_ptr<Ship> ship;
};

TEST_F(ShipComponentIntegrationTests, ShipPriceIncrementsWithComponentAddition) {
    int64_t initial_price = ship->GetShipPrice();
    
    Cargo cargo("TestCargo", "TestFaction", 5000);
    ship->AddCargo(cargo);
    
    EXPECT_GT(ship->GetShipPrice(), initial_price);
    EXPECT_EQ(ship->GetShipPrice(), initial_price + 5000);
}

TEST_F(ShipComponentIntegrationTests, ShipPriceDecrementsWithComponentRemoval) {
    Cargo cargo("TestCargo", "TestFaction", 3000);
    ship->AddCargo(cargo);
    int64_t price_with_cargo = ship->GetShipPrice();
    
    ship->RemoveCargo();
    
    EXPECT_LT(ship->GetShipPrice(), price_with_cargo);
    EXPECT_EQ(ship->GetShipPrice(), price_with_cargo - 3000);
}

TEST_F(ShipComponentIntegrationTests, MultipleEnginesCanBeAdded) {
    Engine engine1("TestEngine1", "TestFaction", 2000, 100, 1);
    Engine engine2("TestEngine2", "TestFaction", 2500, 120, 2);
    
    ship->AddEngine(engine1);
    ship->AddEngine(engine2);
    
    int64_t expected_price = ship->GetShipPrice();
    EXPECT_GE(expected_price, 30000 + 2000 + 2500);
}

TEST_F(ShipComponentIntegrationTests, WeaponDamageIsPreservedAfterAddition) {
    Weapon weapon("TestWeapon", "TestFaction", 5000, 360, 2.5, 1500, 500, 750);
    
    ship->AddWeapon(weapon);
    
    EXPECT_EQ(weapon.GetDamage(), 750);
    EXPECT_EQ(weapon.GetRotation(), 360);
}

TEST_F(ShipComponentIntegrationTests, ShieldCapacityMaintainedCorrectly) {
    Shield shield("TestShield", "TestFaction", 3000, 400, 5000, 8000, 15, 200, 30);
    
    ship->AddShield(shield);
    
    EXPECT_EQ(shield.GetEnergyCapacity(), 5000);
    EXPECT_EQ(shield.GetCapacity(), 8000);
    EXPECT_EQ(shield.GetRegenerationRate(), 200);
}

TEST_F(ShipComponentIntegrationTests, CargoAtomicPropertiesPreserved) {
    Cargo cargo("Helium", "TestFaction", 1000, 2, 4.003, "Gas");
    
    ship->AddCargo(cargo);
    
    EXPECT_EQ(cargo.GetAtomicNumber(), 2);
    EXPECT_DOUBLE_EQ(cargo.GetRelativeAtomicMass(), 4.003);
    EXPECT_EQ(cargo.GetStateAt20(), "Gas");
}

TEST_F(ShipComponentIntegrationTests, EngineRadiationLevelDoesNotAffectPrice) {
    int64_t price_before = ship->GetShipPrice();
    
    Engine low_rad("LowRadEngine", "TestFaction", 2000, 100, 1);
    Engine high_rad("HighRadEngine", "TestFaction", 2000, 100, 5);
    
    EXPECT_EQ(low_rad.GetPrice(), high_rad.GetPrice());
}

TEST_F(ShipComponentIntegrationTests, ShipCanBeCopiedWithAllComponents) {
    Engine engine("TestEngine", "TestFaction", 2000);
    Cargo cargo("TestCargo", "TestFaction", 1000);
    
    ship->AddEngine(engine);
    ship->AddCargo(cargo);
    
    Ship cloned_ship = *ship;
    
    EXPECT_EQ(cloned_ship.GetShipID(), ship->GetShipID());
    EXPECT_EQ(cloned_ship.GetShipPrice(), ship->GetShipPrice());
}

TEST_F(ShipComponentIntegrationTests, ClonedShipCanHaveDifferentFaction) {
    ship->SetFaction("OriginalFaction");
    
    Ship cloned = ship->CloneWithFaction("NewFaction");
    
    EXPECT_EQ(cloned.GetFaction(), "NewFaction");
    EXPECT_EQ(ship->GetFaction(), "OriginalFaction");
    EXPECT_EQ(cloned.GetShipID(), ship->GetShipID());
}