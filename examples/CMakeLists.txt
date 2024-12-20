add_executable(cstring_view_examples examples.cpp)
target_link_libraries(cstring_view_examples PRIVATE cstring_view)

# set the latest CXX standard if it is newer than C++17
set(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS 98 11 14)
list(FIND CPP_UTIL_UNSUPPORTED_CXX_STANDARDS ${CMAKE_CXX_STANDARD_LATEST} CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX)
if(CPP_UTIL_UNSUPPORTED_CXX_STANDARDS_INDEX EQUAL -1)
    message(STATUS "Setting C++ standard to ${CMAKE_CXX_STANDARD_LATEST}.")
    target_compile_features(cstring_view_examples PRIVATE cxx_std_${CMAKE_CXX_STANDARD_LATEST})
else()
    message(FATAL_ERROR "At least C++17 must be supported by the used compiler, but the latest supported standard is ${CMAKE_CXX_STANDARD_LATEST}!")
endif()