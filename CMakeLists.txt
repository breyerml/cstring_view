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
target_include_directories(cstring_view INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(cstring_view INTERFACE cxx_std_17)

set_target_properties(cstring_view PROPERTIES
    PUBLIC_HEADER include/cstring_view.hpp
)

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

# --------------------
# Installation.
# --------------------

include(GNUInstallDirs)

install(
    TARGETS cstring_view
    EXPORT "${PROJECT_NAME}Targets"
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    EXPORT "${PROJECT_NAME}Targets"
    DESTINATION cmake/${PROJECT_NAME}
    NAMESPACE cpp_util::
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    cmake/config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake/${PROJECT_NAME}
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake/${PROJECT_NAME}
)