/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the string operation member functions of the cpp_util::cstring_view class.
 */

#include <cstring>      // std::strcmp
#include <string>       // std::string
#include <string_view>  // std::string_view

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view string operations", "[string_operations]") {
    SECTION("copy") {
        const cpp_util::cstring_view csv{ "Hello, World!" };
        std::string str(5, '\0');

        csv.copy(str.data(), 5);
        CHECK(std::strcmp(str.c_str(), "Hello") == 0);
        csv.copy(str.data(), 5, 7);
        CHECK(std::strcmp(str.c_str(), "World") == 0);
    }

    SECTION("substr") {
        const cpp_util::cstring_view csv{ "foobar" };

        CHECK(csv.substr() == csv);
        CHECK(csv.substr(3) == cpp_util::cstring_view{ "bar" });
        CHECK(csv.substr(1, 2) == std::string_view{ "oo" });
    }

    {
        const cpp_util::cstring_view csv1{ "foo" };
        const cpp_util::cstring_view csv2{ "bar" };
        const cpp_util::cstring_view csv3{ "foobar" };

        SECTION("compare string_view") {
            const cpp_util::cstring_view csv{ "foo" };

            CHECK(csv.compare(csv1) == 0);
            CHECK(csv.compare(csv2) > 0);
            CHECK(csv.compare(csv3) < 0);
        }

        SECTION("compare string_view pos, count") {
            const cpp_util::cstring_view csv{ "  foo  " };

            CHECK(csv.compare(2, 3, csv1) == 0);
            CHECK(csv.compare(2, 3, csv2) > 0);
            CHECK(csv.compare(2, 3, csv3) < 0);
        }

        SECTION("compare string_view pos, count, po2, count2") {
            const cpp_util::cstring_view csv{ "  foo  " };

            CHECK(csv.compare(2, 2, csv1, 0, 3) < 0);
            CHECK(csv.compare(2, 3, csv2, 1, 3) > 0);
            CHECK(csv.compare(2, 3, csv3, 0, 3) == 0);
        }
    }

    {
        const char *csv1{ "foo" };
        const char *csv2{ "bar" };
        const char *csv3{ "foobar" };

        SECTION("compare const char *") {
            const cpp_util::cstring_view csv{ "foo" };

            CHECK(csv.compare(csv1) == 0);
            CHECK(csv.compare(csv2) > 0);
            CHECK(csv.compare(csv3) < 0);
        }

        SECTION("compare const char * pos, count") {
            const cpp_util::cstring_view csv{ "  foo  " };

            CHECK(csv.compare(2, 3, csv1) == 0);
            CHECK(csv.compare(2, 3, csv2) > 0);
            CHECK(csv.compare(2, 3, csv3) < 0);
        }

        SECTION("compare const char * pos, count, count2") {
            const cpp_util::cstring_view csv{ "  foo  " };

            CHECK(csv.compare(2, 2, csv1, 3) < 0);
            CHECK(csv.compare(2, 3, csv2, 3) > 0);
            CHECK(csv.compare(2, 3, csv3, 3) == 0);
        }
    }

    {
        // c-string view to test against
        const cpp_util::cstring_view base{ "Hello, World!" };

        // input data
        const cpp_util::cstring_view csv{ "Hello" };
        const std::string_view sv{ "foo" };
        const char *ptr{ "World" };
        const char c{ '!' };

        SECTION("starts_with") {
            CHECK(base.starts_with(csv));
            CHECK_FALSE(base.starts_with(sv));
            CHECK_FALSE(base.starts_with(ptr));
            CHECK_FALSE(base.starts_with(c));
        }

        SECTION("ends_with") {
            CHECK_FALSE(base.ends_with(csv));
            CHECK_FALSE(base.ends_with(sv));
            CHECK_FALSE(base.ends_with(ptr));
            CHECK(base.ends_with(c));
        }

        SECTION("contains") {
            CHECK(base.contains(csv));
            CHECK_FALSE(base.contains(sv));
            CHECK(base.contains(ptr));
            CHECK(base.contains(c));
        }
    }
}