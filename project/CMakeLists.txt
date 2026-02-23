cmake_minimum_required(VERSION 3.28)

project(Envoxel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Modules
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "cxx_modules")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_STD 1)

# Dependencies
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
find_package(TBB REQUIRED)

# --- Serde library ---

# Core
file(GLOB_RECURSE SERDE_CORE_INTERFACE_UNITS
        CONFIGURE_DEPENDS
        "src/libraries/serde/core/*.ixx"
        "src/libraries/serde/core/*.cppm"
)

file(GLOB_RECURSE SERDE_CORE_IMPLEMENTATIONS
        CONFIGURE_DEPENDS
        "src/libraries/serde/core/*.cpp"
)

add_library(serde_core)

target_sources(serde_core
        PUBLIC
            FILE_SET CXX_MODULES
            BASE_DIRS src/libraries/serde/core
            FILES ${SERDE_CORE_INTERFACE_UNITS}
        PRIVATE
            ${SERDE_CORE_IMPLEMENTATIONS}
)

target_link_libraries(serde_core
        PRIVATE
            Boost::boost
)

# String targets

file(GLOB_RECURSE SERDE_STRING_TARGET_INTERFACE_UNITS
        CONFIGURE_DEPENDS
        "src/libraries/serde/targets/string/*.ixx"
        "src/libraries/serde/targets/string/*.cppm"
)

file(GLOB_RECURSE SERDE_STRING_TARGET_IMPLEMENTATIONS
        CONFIGURE_DEPENDS
        "src/libraries/serde/targets/string/*.cpp"
)

add_library(serde_string_target)

target_sources(serde_string_target
        PUBLIC
            FILE_SET CXX_MODULES
            BASE_DIRS src/libraries/serde/targets/string/
            FILES ${SERDE_STRING_TARGET_INTERFACE_UNITS}
        PRIVATE
            ${SERDE_STRING_TARGET_IMPLEMENTATIONS}
)

target_link_libraries(serde_string_target
        PUBLIC
            serde_core
)

# Tests

# Core tests

file(GLOB_RECURSE SERDE_TESTS
        CONFIGURE_DEPENDS
        "src/libraries/serde/tests/*.cpp"
)

add_executable(serde_tests
        ${SERDE_TESTS}
)

target_link_libraries(serde_tests
        PRIVATE
        serde_core
        serde_string_target
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(serde_tests)