#include <cstring>
#include <iostream>
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
  std::cout << csv.empty() << std::endl << std::endl;

  std::cout << (csv[1] == 'e') << std::endl;
  std::cout << (csv.at(2) == 'l') << std::endl;
  std::cout << (csv.front() == 'H') << std::endl;
  std::cout << (csv.back() == '!') << std::endl;
  std::cout << (std::strcmp(csv.c_str(), "Hello, World!") == 0) << std::endl;
  std::cout << static_cast<std::string_view>(csv) << std::endl;

  auto csv_copy = csv;
  csv_copy.remove_prefix(7);
  std::cout << csv_copy << std::endl;
  auto csv_copy2 = csv;
  std::cout << csv_copy2.substr(7) << std::endl;

  std::cout << csv.compare("12345") << std::endl;
  std::cout << csv.compare("Hello") << std::endl;
  std::cout << csv.compare(csv) << std::endl;

  std::cout << csv.starts_with("Hello") << std::endl;
  std::cout << csv.ends_with("World!") << std::endl;
  std::cout << csv.contains("123") << std::endl;

  std::cout << csv.find("World!") << std::endl;
  std::cout << csv.find('o') << std::endl;
  std::cout << csv.rfind('o') << std::endl;

  std::cout << csv.find_first_of('o') << std::endl;
  std::cout << csv.find_last_of('o') << std::endl;
  std::cout << csv.find_first_not_of("Hl!") << std::endl;
  std::cout << csv.find_last_not_of("Hl!") << std::endl;

  auto csv2 = "Hello, World!"_csv;
  auto csv3 = "12345"_csv;
  std::cout << (csv == csv2) << std::endl;
  std::cout << (csv == csv3) << std::endl;
  std::cout << (csv != csv2) << std::endl;
  std::cout << (csv != csv3) << std::endl;

  std::cout << csv << std::endl;

  return 0;
}
