#include <iostream>
#include <string>
#include <string_view>

#include "cstring_view.hpp"

void print(util::cstring_view str = util::cstring_view{}) { std::cout << str << std::endl; }

int main() {
  {
    print();
    print(util::cstring_view{"cstring_view"});
    print("const char*");
    print(std::string{"std::string"});

    std::string_view sv1{"const char* + length"};
    // explicitly say that string is null-terminated
    util::cstring_view csv1{util::cstring_view::null_terminated, sv1.data(), sv1.length()};
    print(csv1);

    std::string_view sv2{"std::string_view"};
    // explicitly say that string is null-terminated
    util::cstring_view csv2{util::cstring_view::null_terminated, sv2};
    print(csv2);

    char arr[] = "char* + length";
    // explicitly say that string is null-terminated
    print(util::cstring_view{util::cstring_view::null_terminated, arr, 14});
  }

  using namespace util::string_view_literals;
  auto csv = "Hello, World!"_csv;

  for (const char c : csv) {
    std::cout << c << ' ';
  }

  std::cout << std::endl << std::boolalpha;
  std::cout << (csv.size() == csv.length()) << std::endl;
  std::cout << csv.empty() << std::endl;

  return 0;
}
