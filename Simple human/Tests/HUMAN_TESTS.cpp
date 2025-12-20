#include <gtest/gtest.h>
#include "../Header files/HUMAN.h"
#include <sstream>

class HumanTest : public ::testing::Test {
protected:
    Human human = Human("John", "Doe", 1990);
};

// Constructor tests
TEST_F(HumanTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(human.GetFirstName(), "John");
    EXPECT_EQ(human.GetLastName(), "Doe");
    EXPECT_EQ(human.GetBirthYear(), 1990);
}

// First name tests
TEST_F(HumanTest, SetAndGetFirstName) {
    human.SetFirstName("Jane");
    EXPECT_EQ(human.GetFirstName(), "Jane");
}

TEST_F(HumanTest, FirstNameCanBeEmpty) {
    human.SetFirstName("");
    EXPECT_EQ(human.GetFirstName(), "");
}

// Last name tests
TEST_F(HumanTest, SetAndGetLastName) {
    human.SetLastName("Smith");
    EXPECT_EQ(human.GetLastName(), "Smith");
}

TEST_F(HumanTest, LastNameCanBeEmpty) {
    human.SetLastName("");
    EXPECT_EQ(human.GetLastName(), "");
}

// Birth year tests
TEST_F(HumanTest, SetAndGetBirthYear) {
    human.SetBirthYear(1985);
    EXPECT_EQ(human.GetBirthYear(), 1985);
}

TEST_F(HumanTest, BirthYearBoundaryMin) {
    human.SetBirthYear(1900);
    EXPECT_EQ(human.GetBirthYear(), 1900);
}

TEST_F(HumanTest, BirthYearBoundaryMax) {
    human.SetBirthYear(2025);
    EXPECT_EQ(human.GetBirthYear(), 2025);
}

// Inventory tests
TEST_F(HumanTest, AddSingleItemToInventory) {
    human.AddElemToInventory("sword");
    human.WhatIsInInventory();
    EXPECT_FALSE(human.GetFirstName().empty());
}

TEST_F(HumanTest, InventoryInitiallyEmpty) {
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.WhatIsInInventory();
    std::string output = ss.str();
    EXPECT_NE(output.find("inventory:"), std::string::npos);
}

TEST_F(HumanTest, SearchItemInEmptyInventory) {
    std::stringstream ss;
    std::cerr.rdbuf(ss.rdbuf());
    human.IsThisInInventory("sword");
    std::string output = ss.str();
    EXPECT_NE(output.find("Inventory"), std::string::npos);
}

TEST_F(HumanTest, AddMultipleItemsToInventory) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");
    human.AddElemToInventory("helmet");

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.WhatIsInInventory();
    std::string output = ss.str();
    EXPECT_NE(output.find("sword"), std::string::npos);
    EXPECT_NE(output.find("shield"), std::string::npos);
    EXPECT_NE(output.find("helmet"), std::string::npos);
}

TEST_F(HumanTest, RemoveItemFromInventory) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");
    human.RemoveElemFromInventory();

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.WhatIsInInventory();
    std::string output = ss.str();
    EXPECT_EQ(output.find("shield"), std::string::npos);
}

TEST_F(HumanTest, SearchExistingItem) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.IsThisInInventory("sword");
    std::string output = ss.str();
    EXPECT_NE(output.find("found"), std::string::npos);
}

TEST_F(HumanTest, SearchNonExistingItem) {
    human.AddElemToInventory("sword");

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.IsThisInInventory("shield");
    std::string output = ss.str();
    EXPECT_NE(output.find("not found"), std::string::npos);
}

// Trade tests
TEST_F(HumanTest, TradeWithEmptyInventory) {
    Human recipient("Jane", "Smith", 1992);

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.Trade(recipient, "sword");
    std::string output = ss.str();
    EXPECT_NE(output.find("empty"), std::string::npos);
}

TEST_F(HumanTest, TradeExistingItem) {
    Human recipient("Jane", "Smith", 1992);
    human.AddElemToInventory("sword");

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.Trade(recipient, "sword");
    std::string output = ss.str();
    EXPECT_NE(output.find("Successfully sent"), std::string::npos);
}

TEST_F(HumanTest, TradeNonExistingItem) {
    Human recipient("Jane", "Smith", 1992);
    human.AddElemToInventory("sword");

    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());
    human.Trade(recipient, "shield");
    std::string output = ss.str();
    EXPECT_NE(output.find("Cannot send"), std::string::npos);
}

// Operator<< tests
TEST_F(HumanTest, OutputOperatorFormat) {
    std::stringstream ss;
    ss << human;
    std::string output = ss.str();

    EXPECT_NE(output.find("First name:"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
    EXPECT_NE(output.find("Last name:"), std::string::npos);
    EXPECT_NE(output.find("Doe"), std::string::npos);
    EXPECT_NE(output.find("Birth year:"), std::string::npos);
    EXPECT_NE(output.find("1990"), std::string::npos);
}

// Edge cases
TEST_F(HumanTest, NegativeBirthYear) {
    human.SetBirthYear(-100);
    EXPECT_EQ(human.GetBirthYear(), -100);
}

TEST_F(HumanTest, VeryLargeBirthYear) {
    human.SetBirthYear(9999);
    EXPECT_EQ(human.GetBirthYear(), 9999);
}

TEST_F(HumanTest, SpecialCharactersInName) {
    human.SetFirstName("John-Paul");
    human.SetLastName("O'Connor");
    EXPECT_EQ(human.GetFirstName(), "John-Paul");
    EXPECT_EQ(human.GetLastName(), "O'Connor");
}
