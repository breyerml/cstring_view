/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the iterator member functions of the cpp_util::cstring_view class.
 */

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view iterator member functions", "[iterator_support]") {
    const cpp_util::cstring_view csv{ "Hello, World!" };

    REQUIRE(csv.size() == 13);

    SECTION("begin()/cbegin() member functions") {
        CHECK(*csv.begin() == 'H');
        CHECK(*csv.cbegin() == 'H');
    }

    SECTION("end()/cend() member functions") {
        CHECK(*(csv.end() - 1) == '!');
        CHECK(*(csv.cend() - 1) == '!');
    }

    SECTION("rbegin()/crbegin() member functions") {
        CHECK(*csv.rbegin() == '!');
        CHECK(*csv.crbegin() == '!');
    }

    SECTION("rend()/crend() member functions") {
        CHECK(*(csv.rend() - 1) == 'H');
        CHECK(*(csv.crend() - 1) == 'H');
    }
}
