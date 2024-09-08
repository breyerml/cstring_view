/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the capacity member functions of the cpp_util::cstring_view class.
 */

#include <string_view>  // std::string_view

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view capacity member functions", "[capacity]") {
    cpp_util::cstring_view default_csv{};
    cpp_util::cstring_view csv{ "Hello, World!" };

    SECTION("empty() member function") {
        CHECK(default_csv.empty());
        CHECK_FALSE(csv.empty());
    }

    SECTION("size() member function") {
        CHECK(default_csv.size() == 0);
        CHECK(csv.size() == 13);
    }

    SECTION("length() member function") {
        CHECK(default_csv.length() == 0);
        CHECK(csv.length() == 13);
    }

    SECTION("max_size() member function") {
        CHECK(default_csv.max_size() == std::string_view{}.max_size());
        CHECK(csv.max_size() == std::string_view{}.max_size());
    }
}