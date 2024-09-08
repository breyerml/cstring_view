cmake_minimum_required(VERSION 3.30)
project(cstring_view
        VERSION 1.0.1
        DESCRIPTION "Implementation of P1402R0 for a cstring_view."
        LANGUAGES CXX)

add_executable(cstring_view examples.cpp cstring_view.hpp)

# set the latest CXX standard if it is newer than C++17
set(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS 98 11 14)
list(FIND CPP_UTIL_UNSUPPORTED_CXX_STANDARDS ${CMAKE_CXX_STANDARD_LATEST} CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX)
if(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX EQUAL -1)
    message(STATUS "Setting C++ standard to ${CMAKE_CXX_STANDARD_LATEST}.")
    set_property(TARGET cstring_view PROPERTY CXX_STANDARD ${CMAKE_CXX_STANDARD_LATEST})
else()
    message(FATAL_ERROR "At least C++17 must be supported by the used compiler, but the latest supported standard is ${CMAKE_CXX_STANDARD_LATEST}!")
endif()

# enable testing
option(CPP_UTIL_ENABLE_TESTS "Enable testing using Catch2" OFF)
if (CPP_UTIL_ENABLE_TESTS)
    message(STATUS "Enabled testing using Catch2.")
    enable_testing()
    add_subdirectory(tests)
endif ()