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


## function to add test cases using different C++ standards
function(register_test cxx_standard)
    message(STATUS "Generating tests for C++${cxx_standard}.")
    # create executable
    set(CPP_UTIL_TEST_CASE_NAME "test_cases_cxx${cxx_standard}")
    add_executable(${CPP_UTIL_TEST_CASE_NAME} ${CPP_UTIL_CATCH_INCLUDE_DIR}/catch_main.cpp ${CPP_UTIL_TEST_SOURCES})
    target_include_directories(${CPP_UTIL_TEST_CASE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
    # link against Catch
    target_link_libraries(${CPP_UTIL_TEST_CASE_NAME} Catch)
    # set requested C++ standard
    set_property(TARGET cstring_view PROPERTY CXX_STANDARD ${cxx_standard})

    # add test for CTest
    set(CPP_UTIL_TEST_NAME "test_cxx${cxx_standard}")
    add_test(NAME ${CPP_UTIL_TEST_NAME} COMMAND ${CPP_UTIL_TEST_CASE_NAME})
endfunction ()

# generate list of all supported C++ standards
set(CPP_UTIL_CURRENT_CXX_STANDARD ${CMAKE_CXX_STANDARD_LATEST})
set(CPP_UTIL_SUPPORTED_CXX_STANDARDS)
while (NOT ${CPP_UTIL_CURRENT_CXX_STANDARD} EQUAL 17)  # C++17 ist the oldest supported C++ standard for cpp_util::cstring_view
    list(APPEND CPP_UTIL_SUPPORTED_CXX_STANDARDS ${CPP_UTIL_CURRENT_CXX_STANDARD})
    math(EXPR CPP_UTIL_CURRENT_CXX_STANDARD "${CPP_UTIL_CURRENT_CXX_STANDARD} - 3")
endwhile ()
list(APPEND CPP_UTIL_SUPPORTED_CXX_STANDARDS ${CPP_UTIL_CURRENT_CXX_STANDARD})

# register all tests
foreach (CPP_UTIL_CXX_STANDARD IN LISTS CPP_UTIL_SUPPORTED_CXX_STANDARDS)
    register_test(${CPP_UTIL_CXX_STANDARD})
endforeach ()