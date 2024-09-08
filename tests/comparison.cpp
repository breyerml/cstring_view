/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the comparison member functions of the cpp_util::cstring_view class.
 */

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view comparison", "[comparison]") {
    const cpp_util::cstring_view csv1{ "foo" };
    const cpp_util::cstring_view csv2{ "foo" };
    const cpp_util::cstring_view csv3{ "bar" };
    const cpp_util::cstring_view csv4{ "foobar" };

    SECTION("compare equal") {
        CHECK(csv1 == csv2);
        CHECK_FALSE(csv1 == csv3);
        CHECK_FALSE(csv1 == csv4);
    }

    SECTION("compare non-equal") {
        CHECK_FALSE(csv1 != csv2);
        CHECK(csv1 != csv3);
        CHECK(csv1 != csv4);
    }

    SECTION("compare less than") {
        CHECK_FALSE(csv1 < csv2);
        CHECK_FALSE(csv1 < csv3);
        CHECK(csv1 < csv4);
    }

    SECTION("compare greater than") {
        CHECK_FALSE(csv1 > csv2);
        CHECK_FALSE(csv2 > csv1);
        CHECK(csv1 > csv3);
        CHECK_FALSE(csv1 > csv4);
    }

    SECTION("compare less or equal than") {
        CHECK(csv1 <= csv2);
        CHECK_FALSE(csv1 <= csv3);
        CHECK(csv1 <= csv4);
    }

    SECTION("compare greater or equal than") {
        CHECK(csv1 >= csv2);
        CHECK(csv2 >= csv1);
        CHECK(csv1 >= csv3);
        CHECK_FALSE(csv1 >= csv4);
    }
}
