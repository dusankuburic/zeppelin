#include <gtest/gtest.h>
#include "../Header files/HUMAN_DEQUE_MANIPULATION.h"
#include <sstream>

// Mock stdin for testing user input
class DequeManipulationTest : public ::testing::Test {
protected:
    std::deque<Human> humans;

    void SetUp() override {
        humans.clear();
    }

    void CaptureOutput(std::function<void()> func, std::string& output) {
        std::stringstream ss;
        std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
        func();
        std::cout.rdbuf(old_cout);
        output = ss.str();
    }
};

// PrintHumans tests
TEST_F(DequeManipulationTest, PrintHumansEmptyDeque) {
    std::string output;
    CaptureOutput([this]() {
        PrintHumans(humans);
    }, output);

    EXPECT_NE(output.find("empty"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumansWithData) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.push_back(Human("Jane", "Smith", 1992));

    std::string output;
    CaptureOutput([this]() {
        PrintHumans(humans);
    }, output);

    EXPECT_NE(output.find("John"), std::string::npos);
    EXPECT_NE(output.find("Jane"), std::string::npos);
    EXPECT_NE(output.find("OUTPUT"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumansSeparator) {
    humans.push_back(Human("John", "Doe", 1990));

    std::string output;
    CaptureOutput([this]() {
        PrintHumans(humans);
    }, output);

    EXPECT_NE(output.find("======================"), std::string::npos);
}

// PrintHumansInventory tests
TEST_F(DequeManipulationTest, PrintHumansInventoryEmptyDeque) {
    std::string output;
    CaptureOutput([this]() {
        PrintHumansInventory(humans);
    }, output);

    EXPECT_NE(output.find("empty"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumansInventoryWithItems) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");
    humans.at(0).AddElemToInventory("shield");

    humans.push_back(Human("Jane", "Smith", 1992));
    humans.at(1).AddElemToInventory("wand");

    std::string output;
    CaptureOutput([this]() {
        PrintHumansInventory(humans);
    }, output);

    EXPECT_NE(output.find("sword"), std::string::npos);
    EXPECT_NE(output.find("shield"), std::string::npos);
    EXPECT_NE(output.find("wand"), std::string::npos);
}

// PrintHumanInventory tests
TEST_F(DequeManipulationTest, PrintHumanInventoryEmptyDeque) {
    std::string output;
    CaptureOutput([this]() {
        PrintHumanInventory(humans, "John");
    }, output);

    EXPECT_NE(output.find("empty"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumanInventoryFoundByName) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");
    humans.at(0).AddElemToInventory("shield");

    humans.push_back(Human("Jane", "Smith", 1992));
    humans.at(1).AddElemToInventory("wand");

    std::string output;
    CaptureOutput([this]() {
        PrintHumanInventory(humans, "John");
    }, output);

    EXPECT_NE(output.find("sword"), std::string::npos);
    EXPECT_NE(output.find("shield"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumanInventoryNotFound) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    std::string output;
    CaptureOutput([this]() {
        PrintHumanInventory(humans, "Jane");
    }, output);

    // Should not find any items
    EXPECT_EQ(output.find("sword"), std::string::npos);
}

// Test const correctness - this would fail to compile if const correctness is broken
TEST_F(DequeManipulationTest, PrintHumansAcceptsConstDeque) {
    const std::deque<Human>& const_humans = humans;
    humans.push_back(Human("John", "Doe", 1990));

    std::string output;
    CaptureOutput([this, &const_humans]() {
        PrintHumans(const_humans);
    }, output);

    EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumansInventoryAcceptsConstDeque) {
    const std::deque<Human>& const_humans = humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    std::string output;
    CaptureOutput([this, &const_humans]() {
        PrintHumansInventory(const_humans);
    }, output);

    EXPECT_NE(output.find("sword"), std::string::npos);
}

TEST_F(DequeManipulationTest, PrintHumanInventoryAcceptsConstDeque) {
    const std::deque<Human>& const_humans = humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    std::string output;
    CaptureOutput([this, &const_humans]() {
        PrintHumanInventory(const_humans, "John");
    }, output);

    EXPECT_NE(output.find("sword"), std::string::npos);
}

// Multiple humans tests
TEST_F(DequeManipulationTest, MultipleHumansCorrectOutput) {
    for (int i = 0; i < 5; ++i) {
        humans.push_back(Human("Person" + std::to_string(i), "LastName", 1990 + i));
    }

    std::string output;
    CaptureOutput([this]() {
        PrintHumans(humans);
    }, output);

    EXPECT_NE(output.find("Person0"), std::string::npos);
    EXPECT_NE(output.find("Person4"), std::string::npos);
}

// Edge case: Single human
TEST_F(DequeManipulationTest, SingleHumanInDeque) {
    humans.push_back(Human("OnlyOne", "Person", 2000));

    std::string output;
    CaptureOutput([this]() {
        PrintHumans(humans);
    }, output);

    EXPECT_NE(output.find("OnlyOne"), std::string::npos);
}

// Edge case: Empty inventory for multiple humans
TEST_F(DequeManipulationTest, MultipleHumansEmptyInventories) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.push_back(Human("Jane", "Smith", 1992));
    humans.push_back(Human("Bob", "Johnson", 1988));

    std::string output;
    CaptureOutput([this]() {
        PrintHumansInventory(humans);
    }, output);

    // Should show empty inventory for all
    EXPECT_NE(output.find("inventory:"), std::string::npos);
}

// Edge case: Searching by name in large deque
TEST_F(DequeManipulationTest, SearchByNameInLargeDeque) {
    for (int i = 0; i < 10; ++i) {
        std::string name = (i == 5) ? "TargetPerson" : "Person" + std::to_string(i);
        humans.push_back(Human(name, "LastName", 1990 + i));
        if (i == 5) {
            humans.at(i).AddElemToInventory("special_item");
        }
    }

    std::string output;
    CaptureOutput([this]() {
        PrintHumanInventory(humans, "TargetPerson");
    }, output);

    EXPECT_NE(output.find("special_item"), std::string::npos);
}

// Test case sensitivity
TEST_F(DequeManipulationTest, PrintHumanInventoryCaseSensitive) {
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    std::string output;
    CaptureOutput([this]() {
        PrintHumanInventory(humans, "john");  // lowercase
    }, output);

    // Should not find due to case sensitivity
    EXPECT_EQ(output.find("sword"), std::string::npos);
}
