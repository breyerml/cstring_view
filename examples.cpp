#include "cstring_view.hpp"

#include <cstring>      // std::strcmp
#include <iostream>     // std::cout
#include <ios>          // std::boolalpha
#include <string>       // std::string
#include <string_view>  // std::string_view

void print(cpp_util::cstring_view str = cpp_util::cstring_view{});

int main() {
  {
    print();
    print(cpp_util::cstring_view{ "cstring_view" });
    print("const char*");
    print(std::string{ "std::string" });

    std::string_view sv1{ "const char* + length" };
    // explicitly say that string is null-terminated
    cpp_util::cstring_view csv1{ cpp_util::cstring_view::null_terminated, sv1.data(), sv1.length() };
    print(csv1);

    std::string_view sv2{ "std::string_view" };
    // explicitly say that string is null-terminated
    cpp_util::cstring_view csv2{ cpp_util::cstring_view::null_terminated, sv2 };
    print(csv2);

    char arr[] = "char* + length";
    // explicitly say that string is null-terminated
    print(cpp_util::cstring_view{ cpp_util::cstring_view::null_terminated, arr, 14} );
  }

  using namespace cpp_util::string_view_literals;
  auto csv = "Hello, World!"_csv;

  for (const char c : csv) {
    std::cout << c << ' ';
  }

  std::cout << "\n" << std::boolalpha;
  std::cout << (csv.size() == csv.length()) << "\n";
  std::cout << csv.empty() << "\n" << "\n";

  std::cout << (csv[1] == 'e') << "\n";
  std::cout << (csv.at(2) == 'l') << "\n";
  std::cout << (csv.front() == 'H') << "\n";
  std::cout << (csv.back() == '!') << "\n";
  std::cout << (std::strcmp(csv.c_str(), "Hello, World!") == 0) << "\n";
  std::cout << static_cast<std::string_view>(csv) << "\n";

  auto csv_copy = csv;
  csv_copy.remove_prefix(7);
  std::cout << csv_copy << "\n";
  auto csv_copy2 = csv;
  std::cout << csv_copy2.substr(7) << "\n";

  std::cout << csv.compare("12345") << "\n";
  std::cout << csv.compare("Hello") << "\n";
  std::cout << csv.compare(csv) << "\n";

  std::cout << csv.starts_with("Hello") << "\n";
  std::cout << csv.ends_with("World!") << "\n";
  std::cout << csv.contains("123") << "\n";

  std::cout << csv.find("World!") << "\n";
  std::cout << csv.find('o') << "\n";
  std::cout << csv.rfind('o') << "\n";

  std::cout << csv.find_first_of('o') << "\n";
  std::cout << csv.find_last_of('o') << "\n";
  std::cout << csv.find_first_not_of("Hl!") << "\n";
  std::cout << csv.find_last_not_of("Hl!") << "\n";

  auto csv2 = "Hello, World!"_csv;
  auto csv3 = "12345"_csv;
  std::cout << (csv == csv2) << "\n";
  std::cout << (csv == csv3) << "\n";
  std::cout << (csv != csv2) << "\n";
  std::cout << (csv != csv3) << "\n";

  std::cout << csv << "\n";

  return 0;
}

void print(cpp_util::cstring_view str) {
    std::cout << str << "\n";
}