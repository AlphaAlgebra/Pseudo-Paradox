cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(PseudoParadoxEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable aggressive hardware mathematical auto-vectorization optimizations
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -O3 -march=native -ffast-math)
endif()

# Separate directory output layout for clean module builds
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==============================================================================
# AUTOMATIC THIRD-PARTY DEPENDENCY INJECTION (EIGEN & PYBIND11)
# ==============================================================================
include(FetchContent)

# 1. Fetch Eigen Library for Matrix Algorithms
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com
    GIT_TAG        3.4.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(eigen)

# 2. Fetch Pybind11 for Python Interface Layer
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com
    GIT_TAG        v2.12.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(pybind11)

# ==============================================================================
# TARGET EXTENSION COMPILATION DEFINITION
# ==============================================================================
# Define the core binary target library
add_library(quantum_math STATIC
    src/noncommutative.cpp
    src/eigen_solver.cpp
)
target_include_directories(quantum_math PUBLIC include)
target_link_libraries(quantum_math PUBLIC Eigen3::Eigen)

# Compile the native C++ Python extension binary module
pybind11_add_module(pseudo_paradox_core src/bindings.cpp)
target_link_libraries(pseudo_paradox_core PRIVATE quantum_math)

# Automatically place the compiled binary directly into your server folder!
set_target_properties(pseudo_paradox_core PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/server"
)
