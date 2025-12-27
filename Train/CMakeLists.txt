cmake_minimum_required(VERSION 3.10)
project(TrainProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(TrainApp
    src/main.cpp
    src/Cargo.cpp
    src/Wagon.cpp
    src/Train.cpp
)

add_executable(TrainTests
    tests/test_dod.cpp
    src/Cargo.cpp
    src/Wagon.cpp
    src/Train.cpp
)
