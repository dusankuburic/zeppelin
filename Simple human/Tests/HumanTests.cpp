#include <gtest/gtest.h>
#include "../Header files/Human.h"
#include <sstream>

class CaptureStdout {
public:
    CaptureStdout() : old_(std::cout.rdbuf(ss_.rdbuf())) {}
    ~CaptureStdout() { std::cout.rdbuf(old_); }
    std::string str() const { return ss_.str(); }
private:
    std::stringstream ss_;
    std::streambuf* old_;
};

class HumanTest : public ::testing::Test {
protected:
    Human human = Human("John", "Doe", 1990);
};


TEST_F(HumanTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(human.GetFirstName(), "John");
    EXPECT_EQ(human.GetLastName(), "Doe");
    EXPECT_EQ(human.GetBirthYear(), 1990);
}


TEST_F(HumanTest, SetAndGetFirstName) {
    human.SetFirstName("Jane");
    EXPECT_EQ(human.GetFirstName(), "Jane");
}

TEST_F(HumanTest, FirstNameCanBeEmpty) {
    human.SetFirstName("");
    EXPECT_EQ(human.GetFirstName(), "");
}


TEST_F(HumanTest, SetAndGetLastName) {
    human.SetLastName("Smith");
    EXPECT_EQ(human.GetLastName(), "Smith");
}

TEST_F(HumanTest, LastNameCanBeEmpty) {
    human.SetLastName("");
    EXPECT_EQ(human.GetLastName(), "");
}


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


TEST_F(HumanTest, AddSingleItemToInventory) {
    human.AddElemToInventory("sword");
    CaptureStdout capture;
    human.WhatIsInInventory();
    EXPECT_FALSE(human.GetFirstName().empty());
}

TEST_F(HumanTest, InventoryInitiallyEmpty) {
    CaptureStdout capture;
    human.WhatIsInInventory();
    std::string output = capture.str();
    EXPECT_NE(output.find("Inventory is empty"), std::string::npos);
}

TEST_F(HumanTest, SearchItemInEmptyInventory) {
    CaptureStdout capture;
    human.IsThisInInventory("sword");
    std::string output = capture.str();
    EXPECT_NE(output.find("Inventory is empty"), std::string::npos);
}

TEST_F(HumanTest, AddMultipleItemsToInventory) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");
    human.AddElemToInventory("helmet");

    CaptureStdout capture;
    human.WhatIsInInventory();
    std::string output = capture.str();
    EXPECT_NE(output.find("sword"), std::string::npos);
    EXPECT_NE(output.find("shield"), std::string::npos);
    EXPECT_NE(output.find("helmet"), std::string::npos);
}

TEST_F(HumanTest, RemoveItemFromInventory) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");
    human.RemoveElemFromInventory();

    CaptureStdout capture;
    human.WhatIsInInventory();
    std::string output = capture.str();
    EXPECT_EQ(output.find("shield"), std::string::npos);
}

TEST_F(HumanTest, SearchExistingItem) {
    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");

    CaptureStdout capture;
    human.IsThisInInventory("sword");
    std::string output = capture.str();
    EXPECT_NE(output.find("found"), std::string::npos);
}

TEST_F(HumanTest, SearchNonExistingItem) {
    human.AddElemToInventory("sword");

    CaptureStdout capture;
    human.IsThisInInventory("shield");
    std::string output = capture.str();
    EXPECT_NE(output.find("not found"), std::string::npos);
}


TEST_F(HumanTest, TradeWithEmptyInventory) {
    Human recipient("Jane", "Smith", 1992);

    CaptureStdout capture;
    human.Trade(recipient, "sword");
    std::string output = capture.str();
    EXPECT_NE(output.find("empty"), std::string::npos);
}

TEST_F(HumanTest, TradeExistingItem) {
    Human recipient("Jane", "Smith", 1992);
    human.AddElemToInventory("sword");

    CaptureStdout capture;
    human.Trade(recipient, "sword");
    std::string output = capture.str();
    EXPECT_NE(output.find("Successfully sent"), std::string::npos);
}

TEST_F(HumanTest, TradeNonExistingItem) {
    Human recipient("Jane", "Smith", 1992);
    human.AddElemToInventory("sword");

    CaptureStdout capture;
    human.Trade(recipient, "shield");
    std::string output = capture.str();
    EXPECT_NE(output.find("Cannot send"), std::string::npos);
}


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
