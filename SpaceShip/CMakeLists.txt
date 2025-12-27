cmake_minimum_required(VERSION 3.14)
project(SpaceShip)

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
    "src/main.cpp"
    "src/Cargo/CargoImplementation.cpp"
    "src/Engine/EngineImplementation.cpp"
    "src/Shield/ShieldImplementation.cpp"
    "src/Weapon/WeaponImplementation.cpp"
    "src/Ships/SpaceShipImplementation.cpp"
    "src/ShipImplementation.cpp"
    "src/ShipCatalog.cpp"
    "src/ShipFactory.cpp"
    "src/ComponentCatalog.cpp"
    "src/ComponentFactory.cpp"
)

set(MAIN_HEADERS
    "include/Cargo/Cargo.h"
    "include/Cargo/CargoManipulation.h"
    "include/Engine/Engine.h"
    "include/Engine/EngineManipulation.h"
    "include/Shield/Shield.h"
    "include/Shield/ShieldManipulation.h"
    "include/Weapon/Weapon.h"
    "include/Weapon/WeaponManipulation.h"
    "include/Ships/SpaceShip.h"
    "include/Ships/Ship.h"
    "include/Ships/ShipSpec.h"
    "include/Ships/ShipFactory.h"
    "include/InputValidator.h"
    "include/ComponentSpec.h"
    "include/ComponentFactory.h"
)

add_executable(SpaceShip ${MAIN_SOURCES} ${MAIN_HEADERS})

target_include_directories(SpaceShip PRIVATE
    "include"
    "include/Cargo"
    "include/Engine"
    "include/Shield"
    "include/Weapon"
    "include/Ships"
    "include/json"
    "src"
)

enable_testing()

set(TEST_SOURCES
    "tests/BaseComponentTests.cpp"
    "tests/ComponentVariantsTests.cpp"
    "tests/SpaceShipTests.cpp"
    "tests/ShipCatalogTests.cpp"
    "src/Cargo/CargoImplementation.cpp"
    "src/Engine/EngineImplementation.cpp"
    "src/Shield/ShieldImplementation.cpp"
    "src/Weapon/WeaponImplementation.cpp"
    "src/Ships/SpaceShipImplementation.cpp"
    "src/ShipImplementation.cpp"
    "src/ShipCatalog.cpp"
    "src/ShipFactory.cpp"
    "src/ComponentCatalog.cpp"
    "src/ComponentFactory.cpp"
)

add_executable(SpaceShipTests ${TEST_SOURCES} ${MAIN_HEADERS})

target_include_directories(SpaceShipTests PRIVATE
    "include"
    "include/Cargo"
    "include/Engine"
    "include/Shield"
    "include/Weapon"
    "include/Ships"
    "include/json"
    "src"
)

target_link_libraries(SpaceShipTests GTest::gtest GTest::gtest_main)

add_test(NAME SpaceShipTests COMMAND SpaceShipTests)
