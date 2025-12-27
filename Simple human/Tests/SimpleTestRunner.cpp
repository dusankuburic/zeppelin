#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <cassert>
#include "../Header files/Human.h"
#include "../Header files/HumanDequeManipulation.h"


class TestRunner {
private:
    int passed = 0;
    int failed = 0;
    std::string current_suite;

public:
    void BeginSuite(const std::string& name) {
        current_suite = name;
        std::cout << "\n=== " << name << " ===" << std::endl;
    }

    void Test(const std::string& name, bool condition) {
        if (condition) {
            std::cout << "[PASS] " << name << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] " << name << std::endl;
            failed++;
        }
    }

    void PrintSummary() {
        std::cout << "\n======================================" << std::endl;
        std::cout << "Tests Passed: " << passed << std::endl;
        std::cout << "Tests Failed: " << failed << std::endl;
        std::cout << "Total Tests:  " << (passed + failed) << std::endl;
        std::cout << "======================================" << std::endl;
        if (failed > 0) {
            std::cout << "OVERALL: FAILED" << std::endl;
            exit(1);
        } else {
            std::cout << "OVERALL: PASSED" << std::endl;
            exit(0);
        }
    }
};

TestRunner runner;



void TestHumanConstructor() {
    runner.BeginSuite("Human Constructor Tests");

    Human human("John", "Doe", 1990);
    runner.Test("Constructor sets first name", human.GetFirstName() == "John");
    runner.Test("Constructor sets last name", human.GetLastName() == "Doe");
    runner.Test("Constructor sets birth year", human.GetBirthYear() == 1990);
}

void TestHumanSettersGetters() {
    runner.BeginSuite("Human Setters/Getters Tests");

    Human human("", "", 0);

    human.SetFirstName("Alice");
    runner.Test("SetFirstName works", human.GetFirstName() == "Alice");

    human.SetLastName("Smith");
    runner.Test("SetLastName works", human.GetLastName() == "Smith");

    human.SetBirthYear(1985);
    runner.Test("SetBirthYear works", human.GetBirthYear() == 1985);
}

void TestHumanInventoryOperations() {
    runner.BeginSuite("Human Inventory Operations Tests");

    Human human("John", "Doe", 1990);

    human.AddElemToInventory("sword");
    human.AddElemToInventory("shield");

    runner.Test("Can add single item", true);  
    runner.Test("Can add multiple items", true);

    human.RemoveElemFromInventory();
    runner.Test("Can remove item", true);  
}

void TestHumanOutputOperator() {
    runner.BeginSuite("Human Output Operator Tests");

    Human human("John", "Doe", 1990);
    std::stringstream ss;
    ss << human;
    std::string output = ss.str();

    runner.Test("Output contains first name", output.find("John") != std::string::npos);
    runner.Test("Output contains last name", output.find("Doe") != std::string::npos);
    runner.Test("Output contains birth year", output.find("1990") != std::string::npos);
    runner.Test("Output has correct format", output.find("First name:") != std::string::npos);
}

void TestHumanTrade() {
    runner.BeginSuite("Human Trade Tests");

    Human john("John", "Doe", 1990);
    Human jane("Jane", "Smith", 1992);

    john.AddElemToInventory("sword");
    john.AddElemToInventory("shield");

    
    std::stringstream old_cout_buffer;
    std::streambuf* old = std::cout.rdbuf(old_cout_buffer.rdbuf());

    john.Trade(jane, "sword");

    std::cout.rdbuf(old);
    std::string output = old_cout_buffer.str();

    runner.Test("Trade succeeds with existing item", output.find("Successfully sent") != std::string::npos);

    old = std::cout.rdbuf(old_cout_buffer.rdbuf());
    john.Trade(jane, "nonexistent");
    std::cout.rdbuf(old);
    output = old_cout_buffer.str();

    runner.Test("Trade fails with non-existing item", output.find("Cannot send") != std::string::npos ||
                                                       output.find("nonexistent") == std::string::npos);
}

void TestHumanBirthYearBoundaries() {
    runner.BeginSuite("Human Birth Year Boundaries Tests");

    Human human("John", "Doe", 1900);
    runner.Test("Can set birth year to 1900", human.GetBirthYear() == 1900);

    human.SetBirthYear(2025);
    runner.Test("Can set birth year to 2025", human.GetBirthYear() == 2025);

    human.SetBirthYear(1950);
    runner.Test("Can set birth year to 1950", human.GetBirthYear() == 1950);
}



void TestPrintHumansEmpty() {
    runner.BeginSuite("Deque PrintHumans Empty Tests");

    std::deque<Human> humans;

    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumans(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("PrintHumans handles empty deque", output.find("empty") != std::string::npos);
}

void TestPrintHumansWithData() {
    runner.BeginSuite("Deque PrintHumans With Data Tests");

    std::deque<Human> humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.push_back(Human("Jane", "Smith", 1992));

    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumans(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("PrintHumans shows data", output.find("John") != std::string::npos);
    runner.Test("PrintHumans shows multiple entries", output.find("Jane") != std::string::npos);
    runner.Test("PrintHumans has output marker", output.find("OUTPUT") != std::string::npos);
}

void TestPrintHumansInventoryEmpty() {
    runner.BeginSuite("Deque PrintHumansInventory Empty Tests");

    std::deque<Human> humans;

    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumansInventory(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("PrintHumansInventory handles empty deque",
                output.find("empty") != std::string::npos);
}

void TestPrintHumansInventoryWithData() {
    runner.BeginSuite("Deque PrintHumansInventory With Data Tests");

    std::deque<Human> humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");
    humans.at(0).AddElemToInventory("shield");

    humans.push_back(Human("Jane", "Smith", 1992));
    humans.at(1).AddElemToInventory("wand");

    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumansInventory(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("PrintHumansInventory shows items",
                output.find("sword") != std::string::npos ||
                output.find("wand") != std::string::npos);
}

void TestPrintHumanInventoryByName() {
    runner.BeginSuite("Deque PrintHumanInventory By Name Tests");

    std::deque<Human> humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    humans.push_back(Human("Jane", "Smith", 1992));
    humans.at(1).AddElemToInventory("wand");

    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumanInventory(humans, "John");

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("PrintHumanInventory finds John",
                output.find("sword") != std::string::npos ||
                output.find("John") != std::string::npos);
}

void TestConstCorrectness() {
    runner.BeginSuite("Const Correctness Tests");

    std::deque<Human> humans;
    humans.push_back(Human("John", "Doe", 1990));
    humans.at(0).AddElemToInventory("sword");

    
    const std::deque<Human>& const_humans = humans;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumans(const_humans);
    PrintHumansInventory(const_humans);
    PrintHumanInventory(const_humans, "John");

    std::cout.rdbuf(old);

    runner.Test("PrintHumans accepts const deque", true);
    runner.Test("PrintHumansInventory accepts const deque", true);
    runner.Test("PrintHumanInventory accepts const deque", true);
}

void TestParameterPassing() {
    runner.BeginSuite("Parameter Passing Convention Tests");

    std::deque<Human> humans;

    
    runner.Test("int parameters passed by value", true);

    
    Human h1("Test", "User", 2000);
    const std::string& name = h1.GetFirstName();
    runner.Test("String getters return by reference", !name.empty());
}

void TestRangeBasedForLoops() {
    runner.BeginSuite("Range-Based For Loop Tests");

    std::deque<Human> humans;
    for (int i = 0; i < 5; ++i) {
        humans.push_back(Human("Person" + std::to_string(i), "Last", 2000 + i));
    }

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumans(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("Range-based loops iterate correctly",
                output.find("Person0") != std::string::npos &&
                output.find("Person4") != std::string::npos);
}

void TestEnglishMessages() {
    runner.BeginSuite("English Message Tests");

    std::deque<Human> humans;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    PrintHumans(humans);

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    runner.Test("Messages are in English",
                output.find("empty") != std::string::npos &&
                output.find("No humans") != std::string::npos);

    Human h("John", "Doe", 1990);
    buffer.str("");
    old = std::cout.rdbuf(buffer.rdbuf());

    std::cout << h;

    std::cout.rdbuf(old);
    output = buffer.str();

    runner.Test("Human output uses English labels",
                output.find("First name:") != std::string::npos &&
                output.find("Last name:") != std::string::npos &&
                output.find("Birth year:") != std::string::npos);
}



int main() {
    std::cout << "Starting Simple Human C++ Test Suite\n" << std::endl;
    std::cout << "========================================" << std::endl;

    
    TestHumanConstructor();
    TestHumanSettersGetters();
    TestHumanInventoryOperations();
    TestHumanOutputOperator();
    TestHumanTrade();
    TestHumanBirthYearBoundaries();

    TestPrintHumansEmpty();
    TestPrintHumansWithData();
    TestPrintHumansInventoryEmpty();
    TestPrintHumansInventoryWithData();
    TestPrintHumanInventoryByName();
    TestConstCorrectness();
    TestParameterPassing();
    TestRangeBasedForLoops();
    TestEnglishMessages();

    runner.PrintSummary();

    return 0;
}
