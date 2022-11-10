#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "sort.hpp"

TEST(SortTest, TestSort) {
  std::vector<double> v = {4, 1, 5};
  sort(v);
  ASSERT_THAT(v, testing::ElementsAre(1, 4, 5));
}

TEST(SortTest, TestEmpty) {
  std::vector<double> v = {};
  sort(v);
  ASSERT_EQ(0, v.size());
}
