cd ~/Pseudo-Paradox

cat << 'EOF' > core-engine/CMakeLists.txt
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(PseudoParadoxEngine 
    VERSION 1.0.0 
    LANGUAGES CXX
)

# ==============================================================================
# 1. GLOBAL COMPILER CONFIGURATIONS & OPTIMIZATIONS
# ==============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable high-utility compilation diagnostics and aggressive optimization flags
if(MSVC)
    target_compile_options(quantum_math PRIVATE /W4 /WX /O2 /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O3 -march=native -ffast-math)
endif()

# Separate directory output layout for clean build tracking
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==============================================================================
# 2. AUTOMATIC THIRD-PARTY DEPENDENCY INJECTION (EIGEN LINSPACE)
# ==============================================================================
include(FetchContent)

message(STATUS "// INITIATING AUTOMATED FETCH: EIGEN ALGEBRA ENGINE //")
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com
    GIT_TAG        3.4.0
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(eigen)

# ==============================================================================
# 3. TARGET DEFINITION & SOURCE MAPPING
# ==============================================================================
# Define the core shared mathematical binary execution engine
add_library(quantum_math SHARED
    src/noncommutative.cpp
    src/eigen_solver.cpp
)

# Clean, modern, target-based directory management
target_include_directories(quantum_math 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Inject the Eigen template math library straight into your core targets
target_link_libraries(quantum_math 
    PUBLIC 
        Eigen3::Eigen
)

# ==============================================================================
# 4. ARCHITECTURAL SANITY STATUS REPORTING
# ==============================================================================
message(STATUS "=========================================================")
message(STATUS "  PSEUDO-PARADOX C++ CORE COMPILATION CONFIGURATION      ")
message(STATUS "  Target Standard   : C++${CMAKE_CXX_STANDARD}           ")
message(STATUS "  Build Profile     : ${CMAKE_BUILD_TYPE}               ")
message(STATUS "  Compiler ID       : ${CMAKE_CXX_COMPILER_ID}          ")
message(STATUS "=========================================================")
EOF
