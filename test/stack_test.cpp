//
// Created by wjl on 2023/4/25.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE stack_test
#include <boost/test/included/unit_test.hpp>

#include "stack.h"

BOOST_AUTO_TEST_CASE(test_stack_init) {
  Log("==> test stack constructor");
  stl::stack<int> s1;
  s1.print();
  stl::list<int> l{1, 2, 3};
  stl::stack<int> s2(l);
  s2.print();
  stl::stack<int> s3(std::move(l));
  s3.print();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_assignment) {
  Log("==> test stack operator =");
  stl::stack<int> s1({1, 2, 3});
  s1.print();
  stl::stack<int> s2;
  s2 = s1;
  s2.print();
  stl::stack<int> s3;
  s3 = std::move(s1);
  s3.print();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_top) {
  Log("==> test stack top()");
  stl::stack<int> s({1, 2, 3});
  BOOST_CHECK(s.top() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_capacity) {
  Log("==> test stack capacity");
  stl::stack<int> s({1, 2, 3});
  BOOST_CHECK(s.empty() == false);
  BOOST_CHECK(s.size() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_push) {
  Log("==> test stack push()");
  stl::stack<int> s;
  BOOST_CHECK(s.empty() == true);
  BOOST_CHECK(s.size() == 0);
  for (int i = 0; i < 5; i++) {
    s.push(i);
    BOOST_CHECK(s.top() == i);
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_emplace) {
  Log("==> test stack emplace()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::stack<Point2d> s({{1, 1},
                         {2, 2},
                         {3, 3}});
  auto p = s.emplace(5, 5);
  BOOST_CHECK(p.x == 5);
  BOOST_CHECK(p.y == 5);
  BOOST_CHECK(s.top().x == 5);
  BOOST_CHECK(s.top().y == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_pop) {
  Log("==> test stack pop()");
  stl::stack<int> s({1, 2, 3});
  for (int i = 0; i < 3; i++) {
    BOOST_CHECK(s.top() == 3 - i);
    s.pop();
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_stack_swap) {
  Log("==> test stack swap()");
  stl::stack<int> s1({1, 2, 3});
  stl::stack<int> s2({4, 5, 6});
  BOOST_CHECK(s1.top() == 3);
  BOOST_CHECK(s2.top() == 6);
  s1.swap(s2);
  BOOST_CHECK(s1.top() == 6);
  BOOST_CHECK(s2.top() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_operator) {
  Log("==> test operator ==");
  stl::stack<int> s1({1, 2, 3});
  stl::stack<int> s2({1, 2, 3});
  BOOST_CHECK(s1 == s2);
  Log("==> pass!");
}
