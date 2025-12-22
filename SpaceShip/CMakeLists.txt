cmake_minimum_required(VERSION 3.10)
project(SpaceShip)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Test package
find_package(GTest REQUIRED CONFIG)

# ============================================================================
# MAIN EXECUTABLE - SpaceShip Application
# ============================================================================

# Source files for the main application
# Data-oriented: Only base component implementations needed
set(MAIN_SOURCES
    "Source.cpp"
    "SourceFiles/CargoImpl/CargoImplementation.cpp"
    "SourceFiles/EngineImpl/EngineImplementation.cpp"
    "SourceFiles/ShieldImpl/ShieldImplementation.cpp"
    "SourceFiles/WeaponImpl/WeaponImplementation.cpp"
    "SourceFiles/ShipImpl/SpaceShipImplementation.cpp"
    "SourceFiles/ShipImplementation.cpp"
    "SourceFiles/ShipCatalog.cpp"
    "SourceFiles/ShipFactory.cpp"
    "SourceFiles/ComponentCatalog.cpp"
    "SourceFiles/ComponentFactory.cpp"
)

# Header files
# Data-oriented: Only base component headers needed
set(MAIN_HEADERS
    "HeaderFiles/Cargo/Cargo.h"
    "HeaderFiles/Cargo/CargoManipulation.h"
    "HeaderFiles/Engine/Engine.h"
    "HeaderFiles/Engine/EngineManipulation.h"
    "HeaderFiles/Shield/Shield.h"
    "HeaderFiles/Shield/ShieldManipulation.h"
    "HeaderFiles/Weapon/Weapon.h"
    "HeaderFiles/Weapon/WeaponManipulation.h"
    "HeaderFiles/Ships/SpaceShip.h"
    "HeaderFiles/Ships/Ship.h"
    "HeaderFiles/Ships/ShipSpec.h"
    "HeaderFiles/Ships/ShipFactory.h"
    "HeaderFiles/InputValidator.h"
    "HeaderFiles/ComponentSpec.h"
    "HeaderFiles/ComponentFactory.h"
)

# Create main executable
add_executable(SpaceShip ${MAIN_SOURCES} ${MAIN_HEADERS})

# Add include directories for main executable
target_include_directories(SpaceShip PRIVATE
    "HeaderFiles"
    "HeaderFiles/Cargo"
    "HeaderFiles/Engine"
    "HeaderFiles/Shield"
    "HeaderFiles/Weapon"
    "HeaderFiles/Ships"
    "HeaderFiles/json"
    "SourceFiles"
)

# ============================================================================
# TEST EXECUTABLE - SpaceShip Tests
# ============================================================================

enable_testing()

# Test sources (without main application)
# Data-oriented: Only base component implementations needed
set(TEST_SOURCES
    "Tests/BaseComponentTests.cpp"
    "Tests/ComponentVariantsTests.cpp"
    "Tests/SpaceShipTests.cpp"
    "Tests/ShipCatalogTests.cpp"
    # Include implementation files (but NOT Source.cpp which has main())
    "SourceFiles/CargoImpl/CargoImplementation.cpp"
    "SourceFiles/EngineImpl/EngineImplementation.cpp"
    "SourceFiles/ShieldImpl/ShieldImplementation.cpp"
    "SourceFiles/WeaponImpl/WeaponImplementation.cpp"
    "SourceFiles/ShipImpl/SpaceShipImplementation.cpp"
    "SourceFiles/ShipImplementation.cpp"
    "SourceFiles/ShipCatalog.cpp"
    "SourceFiles/ShipFactory.cpp"
    "SourceFiles/ComponentCatalog.cpp"
    "SourceFiles/ComponentFactory.cpp"
)

# Create test executable
add_executable(SpaceShipTests ${TEST_SOURCES} ${MAIN_HEADERS})

# Add include directories for test executable
target_include_directories(SpaceShipTests PRIVATE
    "HeaderFiles"
    "HeaderFiles/Cargo"
    "HeaderFiles/Engine"
    "HeaderFiles/Shield"
    "HeaderFiles/Weapon"
    "HeaderFiles/Ships"
    "HeaderFiles/json"
    "SourceFiles"
)

# Link test executable with Google Test
target_link_libraries(SpaceShipTests GTest::gtest GTest::gtest_main)

# Register tests
add_test(NAME SpaceShipTests COMMAND SpaceShipTests)
