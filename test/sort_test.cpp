//
// Created by wjl on 2023/5/29.
//

#include "sort.h"
#include <gtest/gtest.h>

TEST(sort_test, insertion_sort) {
  stl::vector<int> v{4, 5, 3, 6, 2, 1};
  stl::insertion_sort(v);
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3 ,6, 2, 1};
  int *p = a;
  stl::insertion_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

TEST(sort_test, merge_sort) {
  stl::vector<int> v{1, 3, 2};
  stl::merge_sort(v);
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  stl::vector<int> v1{4, 5, 3, 6, 2, 1};
  stl::merge_sort(v1);
  for (const auto &item: v1) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::merge_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

TEST(sort_test, heap_sort) {
  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::heap_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int b[] = {5, 4, 3, 2, 1};
  int *q = b;
  stl::heap_sort(q, 5);
  for (const auto &item: b) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

TEST(sort_test, quick_sort) {
  stl::vector<int> v1{4, 5, 3, 6, 2, 1};
  stl::quick_sort(v1);
  for (const auto &item: v1) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::quick_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int b[] = {5, 4, 3, 2, 1};
  int *q = b;
  stl::quick_sort(q, 5);
  for (const auto &item: b) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}
