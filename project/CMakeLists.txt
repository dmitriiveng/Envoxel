cmake_minimum_required(VERSION 3.25)

project(Envoxel LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_ROOT /usr/local)
set(Boost_INCLUDEDIR /usr/local/include)
set(Boost_LIBRARYDIR /usr/local/lib)

find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

find_package(TBB REQUIRED)
link_libraries(TBB::tbb)

# engine model

set(MODEL_NAME model_lib)

file(GLOB_RECURSE MODEL_SOURCES "src/engine_model/*.cpp")

add_library(${MODEL_NAME} ${MODEL_SOURCES})

target_include_directories(${MODEL_NAME}
        PUBLIC
        src/engine_model/_include
        ${Boost_INCLUDE_DIRS}
)

# engine model tests

set(ENGINE_MODEL_TESTS tests)

file(GLOB_RECURSE ENGINE_MODEL_TESTS_SOURCES "src/engine_model/unit_tests/*.cpp")

add_executable(${ENGINE_MODEL_TESTS} ${ENGINE_MODEL_TESTS_SOURCES})

target_link_libraries(${ENGINE_MODEL_TESTS}
        PUBLIC
        ${MODEL_NAME}
        gtest
        gtest_main
        pthread
)