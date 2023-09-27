//
// Created by wjl on 2023/5/29.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE sort_test
#include <boost/test/included/unit_test.hpp>

#include <sort.h>

BOOST_AUTO_TEST_CASE(insertion_sort) {
  stl::vector<int> v{4, 5, 3, 6, 2, 1};
  stl::sort::insertion_sort(v);
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::sort::insertion_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

BOOST_AUTO_TEST_CASE(merge_sort) {
  stl::vector<int> v{1, 3, 2};
  stl::sort::merge_sort(v);
  for (const auto &item: v) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  stl::vector<int> v1{4, 5, 3, 6, 2, 1};
  stl::sort::merge_sort(v1);
  for (const auto &item: v1) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::sort::merge_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

BOOST_AUTO_TEST_CASE(heap_sort) {
  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::sort::heap_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int b[] = {5, 4, 3, 2, 1};
  int *q = b;
  stl::sort::heap_sort(q, 5);
  for (const auto &item: b) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

BOOST_AUTO_TEST_CASE(quick_sort) {
  stl::vector<int> v1{4, 5, 3, 6, 2, 1};
  stl::sort::quick_sort(v1);
  for (const auto &item: v1) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int a[] = {4, 5, 3, 6, 2, 1};
  int *p = a;
  stl::sort::quick_sort(p, 6);
  for (const auto &item: a) {
    std::cout << item << " ";
  }
  std::cout << "\n";

  int b[] = {5, 4, 3, 2, 1};
  int *q = b;
  stl::sort::quick_sort(q, 5);
  for (const auto &item: b) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}
