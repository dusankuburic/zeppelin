#include <gtest/gtest.h>
#include "../HeaderFiles/Ships/ShipSpec.h"

class ShipCatalogTests : public ::testing::Test {
protected:
    void SetUp() override {
        try {
            ShipCatalog::GetInstance().Clear();
            ShipCatalog::GetInstance().LoadFromJSON("ships.json");
        } catch (const std::exception& e) {
        }
    }

    void TearDown() override {
        ShipCatalog::GetInstance().Clear();
    }
};

TEST_F(ShipCatalogTests, CatalogCanLoadJSON) {
    ShipCatalog::GetInstance().Clear();
    EXPECT_NO_THROW(ShipCatalog::GetInstance().LoadFromJSON("ships.json"));
}

TEST_F(ShipCatalogTests, CatalogLoadsMultipleShips) {
    EXPECT_GE(ShipCatalog::GetInstance().GetShipCount(), 9);
}

TEST_F(ShipCatalogTests, CatalogContainsExpectedShips) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_TRUE(catalog.HasShip("gunboat_cte12400_condor"));
    EXPECT_TRUE(catalog.HasShip("fighter_mj1_gecko_council"));
    EXPECT_TRUE(catalog.HasShip("capital_liberty_archer_siege_cruiser"));
}

class ShipSpecValidationTests : public ::testing::Test {
};

TEST_F(ShipSpecValidationTests, ValidSpecPasses) {
    ShipSpec spec;
    spec.id = "test_ship";
    spec.name = "Test Ship";
    spec.faction = "TestFaction";
    spec.category = "fighter";
    spec.hull_strength = 1000;
    spec.max_shield_class = 5;
    spec.cargo_space = 100;
    spec.max_impulse_speed = 75;
    spec.base_price = 10000;

    EXPECT_NO_THROW(spec.Validate());
    EXPECT_TRUE(spec.IsValid());
}

TEST_F(ShipSpecValidationTests, EmptyIDFails) {
    ShipSpec spec;
    spec.id = "";
    spec.name = "Test";
    spec.faction = "Test";
    spec.category = "fighter";
    spec.hull_strength = 1000;
    spec.max_shield_class = 5;
    spec.cargo_space = 100;
    spec.max_impulse_speed = 75;
    spec.base_price = 10000;

    EXPECT_THROW(spec.Validate(), std::invalid_argument);
    EXPECT_FALSE(spec.IsValid());
}

TEST_F(ShipSpecValidationTests, InvalidHullStrengthFails) {
    ShipSpec spec;
    spec.id = "test";
    spec.name = "Test";
    spec.faction = "Test";
    spec.category = "fighter";
    spec.hull_strength = 0;
    spec.max_shield_class = 5;
    spec.cargo_space = 100;
    spec.max_impulse_speed = 75;
    spec.base_price = 10000;

    EXPECT_THROW(spec.Validate(), std::invalid_argument);
    EXPECT_FALSE(spec.IsValid());
}

TEST_F(ShipSpecValidationTests, NegativePriceFails) {
    ShipSpec spec;
    spec.id = "test";
    spec.name = "Test";
    spec.faction = "Test";
    spec.category = "fighter";
    spec.hull_strength = 1000;
    spec.max_shield_class = 5;
    spec.cargo_space = 100;
    spec.max_impulse_speed = 75;
    spec.base_price = -1000;

    EXPECT_THROW(spec.Validate(), std::invalid_argument);
    EXPECT_FALSE(spec.IsValid());
}

class ShipCatalogLookupTests : public ShipCatalogTests {
};

TEST_F(ShipCatalogLookupTests, CanFindShipByID) {
    auto& catalog = ShipCatalog::GetInstance();
    const ShipSpec& spec = catalog.GetSpecByID("gunboat_cte12400_condor");
    EXPECT_EQ(spec.name, "Gunboat CTE12400 Condor");
}

TEST_F(ShipCatalogLookupTests, CanFindShipByName) {
    auto& catalog = ShipCatalog::GetInstance();
    const ShipSpec& spec = catalog.GetSpecByName("Gunboat CTE12400 Condor");
    EXPECT_EQ(spec.id, "gunboat_cte12400_condor");
}

TEST_F(ShipCatalogLookupTests, ThrowsOnInvalidID) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_THROW(catalog.GetSpecByID("invalid_ship_id"), std::runtime_error);
}

TEST_F(ShipCatalogLookupTests, ThrowsOnInvalidName) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_THROW(catalog.GetSpecByName("Nonexistent Ship"), std::runtime_error);
}

TEST_F(ShipCatalogLookupTests, HasShipReturnsTrueForExisting) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_TRUE(catalog.HasShip("gunboat_cte12400_condor"));
}

TEST_F(ShipCatalogLookupTests, HasShipReturnsFalseForMissing) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_FALSE(catalog.HasShip("nonexistent_ship"));
}

class ShipCatalogQueryTests : public ShipCatalogTests {
};

TEST_F(ShipCatalogQueryTests, CanGetAllShipIDs) {
    auto& catalog = ShipCatalog::GetInstance();
    auto ids = catalog.GetAllShipIDs();
    EXPECT_GE(ids.size(), 9);
    EXPECT_NE(std::find(ids.begin(), ids.end(), "gunboat_cte12400_condor"), ids.end());
}

TEST_F(ShipCatalogQueryTests, CanGetAllShipNames) {
    auto& catalog = ShipCatalog::GetInstance();
    auto names = catalog.GetAllShipNames();
    EXPECT_GE(names.size(), 9);
    EXPECT_NE(std::find(names.begin(), names.end(), "Gunboat CTE12400 Condor"), names.end());
}

TEST_F(ShipCatalogQueryTests, CanGetShipsByCategory) {
    auto& catalog = ShipCatalog::GetInstance();
    auto gunboats = catalog.GetShipsByCategory("gunboat");
    EXPECT_GE(gunboats.size(), 1);

    auto fighters = catalog.GetShipsByCategory("fighter");
    EXPECT_GE(fighters.size(), 1);

    auto capitals = catalog.GetShipsByCategory("capital");
    EXPECT_GE(capitals.size(), 1);
}

TEST_F(ShipCatalogQueryTests, CategoryShipsHaveCorrectCategory) {
    auto& catalog = ShipCatalog::GetInstance();
    auto gunboats = catalog.GetShipsByCategory("gunboat");

    for (const auto* spec : gunboats) {
        EXPECT_EQ(spec->category, "gunboat");
    }
}

TEST_F(ShipCatalogQueryTests, GetShipCountReturnsNonZero) {
    auto& catalog = ShipCatalog::GetInstance();
    EXPECT_GT(catalog.GetShipCount(), 0);
}

/**
 * ============================================================================
 *  SHIPCATALOG SINGLETON TESTS
 * ============================================================================
 */

class ShipCatalogSingletonTests : public ::testing::Test {
};

TEST_F(ShipCatalogSingletonTests, GetInstanceReturnsSameObject) {
    ShipCatalog& instance1 = ShipCatalog::GetInstance();
    ShipCatalog& instance2 = ShipCatalog::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
}

TEST_F(ShipCatalogSingletonTests, CanClearCatalog) {
    ShipCatalog& catalog = ShipCatalog::GetInstance();
    catalog.LoadFromJSON("ships.json");
    EXPECT_GT(catalog.GetShipCount(), 0);

    catalog.Clear();
    EXPECT_EQ(catalog.GetShipCount(), 0);
}

class ShipCatalogDataTests : public ShipCatalogTests {
};

TEST_F(ShipCatalogDataTests, GunboatHasCorrectData) {
    auto& catalog = ShipCatalog::GetInstance();
    const ShipSpec& gunboat = catalog.GetSpecByID("gunboat_cte12400_condor");

    EXPECT_EQ(gunboat.name, "Gunboat CTE12400 Condor");
    EXPECT_EQ(gunboat.category, "gunboat");
    EXPECT_EQ(gunboat.hull_strength, 125000);
    EXPECT_EQ(gunboat.max_shield_class, 8);
    EXPECT_EQ(gunboat.cargo_space, 450);
    EXPECT_EQ(gunboat.max_impulse_speed, 80);
    EXPECT_EQ(gunboat.base_price, 30000);
}

TEST_F(ShipCatalogDataTests, FighterHasCorrectData) {
    auto& catalog = ShipCatalog::GetInstance();
    const ShipSpec& fighter = catalog.GetSpecByID("fighter_mj1_gecko_council");

    EXPECT_EQ(fighter.name, "Fighter MJ1 Gecko Council");
    EXPECT_EQ(fighter.category, "fighter");
    EXPECT_EQ(fighter.hull_strength, 4100);
    EXPECT_EQ(fighter.max_shield_class, 8);
    EXPECT_EQ(fighter.cargo_space, 45);
    EXPECT_EQ(fighter.max_impulse_speed, 80);
    EXPECT_EQ(fighter.base_price, 12356);
}

TEST_F(ShipCatalogDataTests, CapitalHasCorrectData) {
    auto& catalog = ShipCatalog::GetInstance();
    const ShipSpec& capital = catalog.GetSpecByID("capital_liberty_archer_siege_cruiser");

    EXPECT_EQ(capital.name, "Capital Liberty Archer Siege Cruiser");
    EXPECT_EQ(capital.category, "capital");
    EXPECT_EQ(capital.hull_strength, 295000);
    EXPECT_EQ(capital.max_shield_class, 9);
    EXPECT_EQ(capital.cargo_space, 800);
    EXPECT_EQ(capital.max_impulse_speed, 70);
    EXPECT_EQ(capital.base_price, 57233);
}

TEST_F(ShipCatalogDataTests, AllShipsHaveValidPrices) {
    auto& catalog = ShipCatalog::GetInstance();
    auto ids = catalog.GetAllShipIDs();

    for (const auto& id : ids) {
        const ShipSpec& spec = catalog.GetSpecByID(id);
        EXPECT_GE(spec.base_price, 0) << "Ship " << id << " has invalid price";
    }
}

TEST_F(ShipCatalogDataTests, AllShipsHaveValidHullStrength) {
    auto& catalog = ShipCatalog::GetInstance();
    auto ids = catalog.GetAllShipIDs();

    for (const auto& id : ids) {
        const ShipSpec& spec = catalog.GetSpecByID(id);
        EXPECT_GT(spec.hull_strength, 0) << "Ship " << id << " has invalid hull strength";
    }
}
