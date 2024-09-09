/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the non-member functions of the cpp_util::cstring_view class.
 */

#include "cstring_view.hpp"

#include "catch/catch.hpp"

#include <cstring>      // std::strcmp
#include <sstream>      // std::ostringstream
#include <string>       // std::string
#include <string_view>  // std::string_view, std::basic_string_view, std::hash

#if __has_include(<format>)

#include <format>  // std::format

#endif

TEST_CASE("cstring_view non-member functions", "[non_member_function]") {
    SECTION("stream insertion operator") {
        const cpp_util::cstring_view csv{ "Hello, World!" };
        std::ostringstream out{};

        out << csv;
        CHECK(out.str() == std::string{ "Hello, World!" });
    }

#if defined(__cpp_lib_format)
    SECTION("std::format") {
        const cpp_util::cstring_view csv{ "Hello, World!" };
        std::ostringstream out{};

        out << std::format("{}", csv);
        CHECK(out.str() == std::string{ "Hello, World!" });
    }
#endif

    SECTION("swap() free function") {
        cpp_util::cstring_view csv1{ "foo" };
        cpp_util::cstring_view csv2{ "bar" };

        cpp_util::swap(csv1, csv2);
        CHECK(std::strcmp(csv1.c_str(), "bar") == 0);
        CHECK(std::strcmp(csv2.c_str(), "foo") == 0);

        std::swap(csv1, csv2);
        CHECK(std::strcmp(csv1.c_str(), "foo") == 0);
        CHECK(std::strcmp(csv2.c_str(), "bar") == 0);
    }
}

TEST_CASE("cstring_view literals", "[literals]") {
    using namespace cpp_util::string_view_literals;
    using namespace std::string_view_literals;

    SECTION("cstring_view") {
        const cpp_util::cstring_view csv = "Hello, World!"_csv;
        const std::string_view sv = "Hello, World!"sv;
        CHECK(static_cast<std::string_view>(csv) == sv);
    }

#if defined(__cpp_char8_t)
    SECTION("u8cstring_view") {
        const cpp_util::u8cstring_view csv = u8"Hello, World!"_csv;
        const std::u8string_view sv = u8"Hello, World!"sv;
        CHECK(static_cast<std::u8string_view>(csv) == sv);
    }
#endif

    SECTION("u16cstring_view") {
        const cpp_util::u16cstring_view csv = u"Hello, World!"_csv;
        const std::u16string_view sv = u"Hello, World!"sv;
        CHECK(static_cast<std::u16string_view>(csv) == sv);
    }

    SECTION("u32cstring_view") {
        const cpp_util::u32cstring_view csv = U"Hello, World!"_csv;
        const std::u32string_view sv = U"Hello, World!"sv;
        CHECK(static_cast<std::u32string_view>(csv) == sv);
    }

    SECTION("wcstring_view") {
        const cpp_util::wcstring_view csv = L"Hello, World!"_csv;
        const std::wstring_view sv = L"Hello, World!"sv;
        CHECK(static_cast<std::wstring_view>(csv) == sv);
    }
}

TEST_CASE("cstring_view hashing", "[hash]") {
    SECTION("cstring_view") {
        const cpp_util::cstring_view csv{ "foo" };
        const std::string_view sv{ "foo" };

        CHECK(std::hash<cpp_util::cstring_view>{}(csv) == std::hash<std::string_view>{}(sv));
    }

#if defined(__cpp_char8_t)
    SECTION("u8cstring_view") {
        const cpp_util::u8cstring_view csv{ u8"foo" };
        const std::u8string_view sv{ u8"foo" };

        CHECK(std::hash<cpp_util::u8cstring_view>{}(csv) == std::hash<std::u8string_view>{}(sv));
    }
#endif

    SECTION("u16cstring_view") {
        const cpp_util::u16cstring_view csv{ u"foo" };
        const std::u16string_view sv{ u"foo" };

        CHECK(std::hash<cpp_util::u16cstring_view>{}(csv) == std::hash<std::u16string_view>{}(sv));
    }

    SECTION("u32cstring_view") {
        const cpp_util::u32cstring_view csv{ U"foo" };
        const std::u32string_view sv{ U"foo" };

        CHECK(std::hash<cpp_util::u32cstring_view>{}(csv) == std::hash<std::u32string_view>{}(sv));
    }

    SECTION("wcstring_view") {
        const cpp_util::wcstring_view csv{ L"foo" };
        const std::wstring_view sv{ L"foo" };

        CHECK(std::hash<cpp_util::wcstring_view>{}(csv) == std::hash<std::wstring_view>{}(sv));
    }
}
