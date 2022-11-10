#include <print.hpp>

void print(const std::vector<double> &list) {
  for (auto item : list) {
    std::cout << item << ' ';
  }
  std::cout << std::endl;
}