cmake_minimum_required(VERSION 3.15)
project(Bank_emulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

file(GLOB_RECURSE CORE_SOURCES 
    "src/**/*.cpp" 
)

list(REMOVE_ITEM CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(Bank_sustem src/main.cpp ${CORE_SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(SystemTests ${TEST_SOURCES} ${CORE_SOURCES})



target_link_libraries(SystemTests GTest::gtest_main GTest::gtest)
include(GoogleTest)
gtest_discover_tests(SystemTests)