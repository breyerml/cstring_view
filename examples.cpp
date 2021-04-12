#include "cstring_view.hpp"
#include <iostream>

int main() {
  util::cstring_view csv{"Hello, World!"};
  std::cout << csv << std::endl;
  return 0;
}
