cmake_minimum_required(VERSION 3.10)
project(SimpleHuman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test package
find_package(GTest REQUIRED CONFIG)

# Source files for the main application
set(SOURCES
    "Simple human/HUMAN_IMPLEMENTATION.cpp"
    "Simple human/Main.cpp"
)

set(HEADERS
    "Simple human/Header files/HUMAN.h"
    "Simple human/Header files/INVENTORY_MANIPULATION.h"
    "Simple human/Header files/HUMAN_DEQUE_MANIPULATION.h"
)

# Create main executable
add_executable(SimpleHuman ${SOURCES} ${HEADERS})
target_include_directories(SimpleHuman PRIVATE "Simple human/Header files")

# Test executable
enable_testing()

set(TEST_SOURCES
    "Simple human/Tests/HumanTests.cpp"
    "Simple human/Tests/DequeManipulationTests.cpp"
    "Simple human/HUMAN_IMPLEMENTATION.cpp"
)

add_executable(SimpleHumanTests ${TEST_SOURCES} ${HEADERS})
target_include_directories(SimpleHumanTests PRIVATE "Simple human/Header files")
target_link_libraries(SimpleHumanTests GTest::gtest GTest::gtest_main)

add_test(NAME SimpleHumanTests COMMAND SimpleHumanTests)
