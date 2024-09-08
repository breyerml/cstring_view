cmake_minimum_required(VERSION 3.20)
project(cstring_view
        VERSION 1.0.1
        DESCRIPTION "Implementation of P1402R0 for a cstring_view."
        LANGUAGES CXX)

add_executable(cstring_view examples.cpp cstring_view.hpp)


include(CheckCXXCompilerFlag)

# Check for standard to use
check_cxx_compiler_flag(-std=c++20 CPP_UTIL_HAS_FLAG_STD_CXX20)
check_cxx_compiler_flag(-std=c++17 CPP_UTIL_HAS_FLAG_STD_CXX17)
if (CPP_UTIL_HAS_FLAG_STD_CXX20)
    target_compile_features(cstring_view PRIVATE cxx_std_20)
elseif (CPP_UTIL_HAS_FLAG_STD_CXX17)
    target_compile_features(cstring_view PRIVATE cxx_std_17)
else ()
    message(FATAL_ERROR "At least C++17 must be supported by the used compiler!")
endif ()

# enable testing
option(CPP_UTIL_ENABLE_TESTS "Enable testing using Catch2" OFF)
if (CPP_UTIL_ENABLE_TESTS)
    message(STATUS "Enabled testing using Catch2.")
    enable_testing()
    add_subdirectory(tests)
endif ()