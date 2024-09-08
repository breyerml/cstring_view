# add catch library
set(CPP_UTIL_CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CPP_UTIL_CATCH_INCLUDE_DIR})

# specify test source files and build executable
set(CPP_UTIL_TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/construction_and_assignment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/iterators.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/capacity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/element_access.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/modifiers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/string_operations.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/searching.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/comparison.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/non_member_functions.cpp
)


# function to add test cases using different C++ standards
include(CheckCXXCompilerFlag)
function(register_test cxx_standard_flag)
    # if MSVC is used, change compiler flag
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        string(REPLACE "=" ":" cxx_standard_flag ${cxx_standard_flag})
    endif ()
    string(SUBSTRING ${cxx_standard_flag} 8 -1 CXX_STANDARD_VALUE)

    # check if compiler flag is supported
    check_cxx_compiler_flag(${cxx_standard_flag} HAS_FLAG_STD_CXX_${CXX_STANDARD_VALUE})
    if (${HAS_FLAG_STD_CXX_${CXX_STANDARD_VALUE}})
        # create executable
        string(SUBSTRING ${cxx_standard_flag} 8 -1 CXX_STANDARD_VALUE)
        set(CPP_UTIL_TEST_CASE_NAME "test_cases_cxx${CXX_STANDARD_VALUE}")
        add_executable(${CPP_UTIL_TEST_CASE_NAME} ${CPP_UTIL_CATCH_INCLUDE_DIR}/catch_main.cpp ${CPP_UTIL_TEST_SOURCES})
        target_include_directories(${CPP_UTIL_TEST_CASE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
        # link against Catch
        target_link_libraries(${CPP_UTIL_TEST_CASE_NAME} Catch)
        # set requested C++ standard
        target_compile_options(${CPP_UTIL_TEST_CASE_NAME} PUBLIC ${cxx_standard_flag})

        # add test for CTest
        set(CPP_UTIL_TEST_NAME "test_cxx${CXX_STANDARD_VALUE}")
        add_test(NAME ${CPP_UTIL_TEST_NAME} COMMAND ${CPP_UTIL_TEST_CASE_NAME})
    endif ()
    unset(${HAS_FLAG_STD_CXX_${CXX_STANDARD_VALUE}} CACHE)
endfunction()


# register tests
register_test(-std=c++17)
register_test(-std=c++20)
register_test(-std=c++23)