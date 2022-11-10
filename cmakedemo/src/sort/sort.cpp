#include <sort.hpp>

int sort(std::vector<double>& list) {
  try {
    std::sort(list.begin(), list.end());
  } catch (const std::exception) {
    return -1;
  }
  return 0;
}