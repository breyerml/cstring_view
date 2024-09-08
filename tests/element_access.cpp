/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the element access member functions of the cpp_util::cstring_view class.
 */

#include <cstddef>      // std::size_t
#include <string_view>  // std::string_view

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view element access member functions", "[element_access]") {
    cpp_util::cstring_view csv{ "012345" };
    const cpp_util::cstring_view const_csv{ "012345" };
    cpp_util::cstring_view default_csv{};

    REQUIRE(const_csv.size() == 6);
    REQUIRE(default_csv.empty());

    SECTION("operator[] member function") {
        for (std::size_t i = 0; i < 6; ++i) {
            CHECK(csv[i] == static_cast<char>('0' + i));
            CHECK(const_csv[i] == static_cast<char>('0' + i));
        }
    }

    SECTION("at() member function") {
        for (std::size_t i = 0; i < 6; ++i) {
            CHECK(csv.at(i) == static_cast<char>('0' + i));
            CHECK(const_csv.at(i) == static_cast<char>('0' + i));
        }

        CHECK_THROWS_AS(csv.at(6), std::out_of_range);
        CHECK_THROWS_AS(const_csv.at(6), std::out_of_range);
        CHECK_THROWS_AS(default_csv.at(0), std::out_of_range);
    }

    SECTION("front() member function") {
        CHECK(csv.front() == '0');
        CHECK(const_csv.front() == '0');
    }

    SECTION("back() member function") {
        CHECK(csv.back() == '5');
        CHECK(const_csv.back() == '5');
    }

    SECTION("data() member function") {
        CHECK(csv.data() == &csv[0]);
        CHECK(const_csv.data() == &const_csv[0]);
    }

    SECTION("c_str() member function") {
        CHECK(csv.c_str() == &csv[0]);
        CHECK(const_csv.c_str() == &const_csv[0]);
    }

    SECTION("std::string_view operator() member function") {
        const std::string_view sv{ "012345" };
        CHECK(static_cast<std::string_view>(csv) == sv);
        CHECK(static_cast<std::string_view>(const_csv) == sv);
    }
}
