/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the searching member functions of the cpp_util::cstring_view class.
 */

#include <string_view>  // std::string_view
#include <cstring>      // std::strcmp

#include "catch/catch.hpp"
#include "cstring_view.hpp"

TEST_CASE("cstring_view searching", "[searching]") {
    {
        // c-string view to test against
        const cpp_util::cstring_view base{ " long long int" };

        // input data
        const cpp_util::cstring_view csv{ "long" };
        const std::string_view sv{ "on" };
        const char c{ 'o' };
        const char *ptr{ "long" };
        const char *ptr2{ "long double" };

        SECTION("find") {
            CHECK(base.find(csv) == 1);
            CHECK(base.find(csv, 2) == 6);
            CHECK(base.find(sv, 8) == cpp_util::cstring_view::npos);

            CHECK(base.find(c) == 2);
            CHECK(base.find(c, 8) == cpp_util::cstring_view::npos);

            CHECK(base.find(ptr2, 5, 4) == 6);
            CHECK(base.find(ptr) == 1);
            CHECK(base.find(ptr, 2) == 6);
        }

        SECTION("rfind") {
            CHECK(base.rfind(csv) == 6);
            CHECK(base.rfind(csv, 2) == 1);
            CHECK(base.rfind(sv, 8) == 7);

            CHECK(base.rfind(c) == 7);
            CHECK(base.rfind(c, 1) == cpp_util::cstring_view::npos);

            CHECK(base.rfind(ptr2, 5, 4) == 1);
            CHECK(base.rfind(ptr) == 6);
            CHECK(base.rfind(ptr, 2) == 1);
        }
    }

    {
        // c-string view to test against
        const cpp_util::cstring_view base{ "abbacba" };

        // input data
        const cpp_util::cstring_view csv{ "bc" };
        const std::string_view sv{ "ab" };
        const char c{ 'c' };
        const char *ptr{ "efa" };

        SECTION("find_first_of") {
            CHECK(base.find_first_of(csv) == 1);
            CHECK(base.find_first_of(csv, 2) == 2);
            CHECK(base.find_first_of(sv) == 0);

            CHECK(base.find_first_of(c) == 4);
            CHECK(base.find_first_of(c, 5) == cpp_util::cstring_view::npos);

            CHECK(base.find_first_of(ptr) == 0);
            CHECK(base.find_first_of(ptr, 1) == 3);
            CHECK(base.find_first_of(ptr, 0, 2) == cpp_util::cstring_view::npos);
        }

        SECTION("find_last_of") {
            CHECK(base.find_last_of(csv) == 5);
            CHECK(base.find_last_of(csv, 2) == 2);
            CHECK(base.find_last_of(sv) == 6);

            CHECK(base.find_last_of(c) == 4);
            CHECK(base.find_last_of(c, 3) == cpp_util::cstring_view::npos);

            CHECK(base.find_last_of(ptr) == 6);
            CHECK(base.find_last_of(ptr, 1) == 0);
            CHECK(base.find_last_of(ptr, 0, 2) == cpp_util::cstring_view::npos);
        }

        SECTION("find_first_not_of") {
            CHECK(base.find_first_not_of(csv) == 0);
            CHECK(base.find_first_not_of(csv, 2) == 3);
            CHECK(base.find_first_not_of(sv) == 4);

            CHECK(base.find_first_not_of(c) == 0);
            CHECK(base.find_first_not_of(c, 5) == 5);

            CHECK(base.find_first_not_of(ptr) == 1);
            CHECK(base.find_first_not_of(ptr, 1) == 1);
            CHECK(base.find_first_not_of(ptr, 0, 2) == 0);
        }

        SECTION("find_last_not_of") {
            CHECK(base.find_last_not_of(csv) == 6);
            CHECK(base.find_last_not_of(csv, 2) == 0);
            CHECK(base.find_last_not_of(sv) == 4);

            CHECK(base.find_last_not_of(c) == 6);
            CHECK(base.find_last_not_of(c, 5) == 5);

            CHECK(base.find_last_not_of(ptr) == 5);
            CHECK(base.find_last_not_of(ptr, 1) == 1);
            CHECK(base.find_last_not_of(ptr, 0, 2) == 0);
        }
    }
}