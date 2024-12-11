cmake_minimum_required(VERSION 3.30)
project(cstring_view
        VERSION 1.0.1
        DESCRIPTION "Implementation of P1402R0 for a cstring_view."
        LANGUAGES CXX)

# --------------------
# Options.
# --------------------

option(CPP_UTIL_BUILD_EXAMPLES "Build examples")
option(CPP_UTIL_ENABLE_TESTS "Enable testing using Catch2")

# --------------------
# Project Targets.
# --------------------

add_library(cstring_view INTERFACE)
target_include_directories(cstring_view INTERFACE include)
target_compile_features(cstring_view INTERFACE cxx_std_17)

# --------------------
# Examples.
# --------------------

if (CPP_UTIL_BUILD_EXAMPLES)
    message(STATUS "Build examples.")
    add_subdirectory(examples)
endif()

# --------------------
# Testing.
# --------------------

if (CPP_UTIL_ENABLE_TESTS)
    message(STATUS "Enabled testing using Catch2.")
    enable_testing()
    add_subdirectory(tests)
endif ()