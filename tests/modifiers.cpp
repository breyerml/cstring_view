/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the modifier member functions of the cpp_util::cstring_view class.
 */

#include "cstring_view.hpp"

#include "catch/catch.hpp"

#include <cstring>  // std::strcmp

TEST_CASE("cstring_view modifiers", "[modifier]") {
    cpp_util::cstring_view csv1{ "foo" };
    cpp_util::cstring_view csv2{ "bar" };

    SECTION("remove prefix") {
        csv1.remove_prefix(0);
        CHECK(std::strcmp(csv1.c_str(), "foo") == 0);
        csv1.remove_prefix(2);
        CHECK(std::strcmp(csv1.c_str(), "o") == 0);
        csv1.remove_prefix(1);
        CHECK(std::strcmp(csv1.c_str(), "") == 0);
    }

    SECTION("swap") {
        csv1.swap(csv2);
        CHECK(std::strcmp(csv1.c_str(), "bar") == 0);
        CHECK(std::strcmp(csv2.c_str(), "foo") == 0);
    }
}
