/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the constructors and assignment operators of the cpp_util::cstring_view class.
 */

#include "cstring_view.hpp"

#include "catch/catch.hpp"

#include <algorithm>    // std::equal
#include <cstring>      // std::strcmp
#include <string>       // std::string
#include <string_view>  // std::string_view

TEST_CASE("cstring_view constructors", "[construction]") {
    SECTION("default constructor") {
        const cpp_util::cstring_view csv{};

        CHECK(static_cast<std::string_view>(csv) == std::string_view{});
        CHECK(csv.empty());
        CHECK(csv.data() == nullptr);
    }

    SECTION("copy constructor") {
        const cpp_util::cstring_view csv1{ "Hello, World!" };
        const cpp_util::cstring_view csv2{ csv1 };

        REQUIRE(csv1.size() == csv2.size());
        CHECK(std::equal(csv1.cbegin(), csv1.cend(), csv2.cbegin()));
    }

    SECTION("const char * constructor") {
        const cpp_util::cstring_view csv{ "Hello, World!" };

        CHECK(std::strcmp(csv.c_str(), "Hello, World!") == 0);
    }

    SECTION("std::string constructor") {
        const std::string str{ "Hello, World!" };
        const cpp_util::cstring_view csv{ str };

        CHECK(std::strcmp(csv.c_str(), str.c_str()) == 0);
    }

    SECTION("null-terminated const char * + size constructor") {
        const std::string_view sv{ "Hello, World!" };
        const cpp_util::cstring_view csv{ cpp_util::cstring_view::null_terminated, sv.data(), sv.length() };

        CHECK(std::strcmp(csv.c_str(), sv.data()) == 0);
    }

    SECTION("null-terminated std::string_view constructor") {
        const std::string_view sv{ "Hello, World!" };
        const cpp_util::cstring_view csv{ cpp_util::cstring_view::null_terminated, sv };

        CHECK(std::strcmp(csv.c_str(), sv.data()) == 0);
    }
}

TEST_CASE("cstring_view assignment", "[assignment]") {
    cpp_util::cstring_view csv1{ "foo" };
    const cpp_util::cstring_view csv2{ "bar" };
    const cpp_util::cstring_view csv3{ "foobar" };

    REQUIRE(csv1.size() == 3);
    REQUIRE(csv2.size() == 3);
    REQUIRE(csv3.size() == 6);

    SECTION("copy-assignment operator") {
        csv1 = csv2;
        REQUIRE(csv1.size() == csv2.size());
        CHECK(std::equal(csv1.cbegin(), csv1.cend(), csv2.cbegin()));

        csv1 = csv3;
        REQUIRE(csv1.size() == csv3.size());
        CHECK(std::equal(csv1.cbegin(), csv1.cend(), csv3.cbegin()));
    }
}
