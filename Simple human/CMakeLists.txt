cmake_minimum_required(VERSION 3.14)
project(SimpleHuman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(MAIN_SOURCES
    "HumanImplementation.cpp"
    "Main.cpp"
)

set(MAIN_HEADERS
    "Header files/Human.h"
    "Header files/HumanDequeManipulation.h"
    "Header files/InventoryManipulation.h"
)

add_executable(SimpleHuman ${MAIN_SOURCES} ${MAIN_HEADERS})

target_include_directories(SimpleHuman PRIVATE
    "Header files"
)

enable_testing()

set(TEST_SOURCES
    "Tests/DequeManipulationTests.cpp"
    "Tests/HumanTests.cpp"
    "HumanImplementation.cpp"
)

add_executable(SimpleHumanTests ${TEST_SOURCES} ${MAIN_HEADERS})

target_include_directories(SimpleHumanTests PRIVATE
    "Header files"
)

target_link_libraries(SimpleHumanTests GTest::gtest GTest::gtest_main)

add_test(NAME SimpleHumanTests COMMAND SimpleHumanTests)
