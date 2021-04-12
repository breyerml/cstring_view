cmake_minimum_required(VERSION 3.19)
project(cstring_view
        VERSION 1.0.0
        DESCRIPTION "Implementation of P1402R0 for a cstring_view."
        LANGUAGES CXX)

add_executable(cstring_view examples.cpp cstring_view.hpp)

target_compile_features(cstring_view PUBLIC cxx_std_17)

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(cstring_view PUBLIC /W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    target_compile_options(cstring_view PUBLIC -Wall -Wextra -pedantic -Werror)
endif ()