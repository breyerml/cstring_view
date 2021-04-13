# cstring_view

Implementation of P1402R0 for a `cstring_view`.

Mimics (and delegates most of its functionality to) a `std::basic_string_view`, but removes all functions that could
potentially break the invariant of null termination.

## Changes compared to P1402R0

- The conversion from a `std::string` to a `basic_cstring_view` is implemented using a special constructor, since it is
  not possible to add a function to the `std::basic_string` class.
- Moved the `null_terminated_t` into the `basic_cstring_view` class definition.
- Enabled all `char8_t` functionality only conditionally if `__cplusplus == 202002L`.
- Renamed the suffix literal for a `basic_cstring_view` from `csv` to `_csv` since only standard library suffixes can
  omit the `_`.
- Corrected `constexpr string_view_type substr(size_type pos = 0, size_type n) const;` and removed the default parameter
  from the first parameter.
- Enabled `starts_with` and `ends_with` delegation to `std::string_view` only if `__cplusplus == 202002L`, otherwise a
  custom implementation based on *cppreference* is used.
- Added `contains()` functions proposed for C++23.
- Added `assert()` to various functions.
- Implemented the comparison functions using a defaulted `operator<=>`if `__cplusplus == 202002L`.
- Added ranges helper templates, which are only enabled if `__cplusplus == 202002L && __has_include(<ranges>)`.

## Usage

Simply copy the `cstring_view.hpp` file to your project folder (and change the namespace `util` to something more
sophisticated).

The minimum required compiler versions are GCC 7.1 (GCC 11.1 for all features) or clang 5.0.0 (clang 11.0.0 for all
features). MSVC hasn't been tested.

## Building the examples

```bash
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --target cstring_view --config Debug
$ ./cstring_view
```