//
// Created by wjl on 2023/4/25.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE queue_test
#include <boost/test/included/unit_test.hpp>

#include <queue.h>

BOOST_AUTO_TEST_CASE(queue_init) {
  Log("==> test queue constructor");
  stl::queue<int> s1;
  s1.print();
  stl::list<int> l{1, 2, 3};
  stl::queue<int> s2(l);
  s2.print();
  stl::queue<int> s3(std::move(l));
  s3.print();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_assignment) {
  Log("==> test queue operator =");
  stl::queue<int> s1({1, 2, 3});
  s1.print();
  stl::queue<int> s2;
  s2 = s1;
  s2.print();
  stl::queue<int> s3;
  s3 = std::move(s1);
  s3.print();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_front_back) {
  Log("==> test queue front() and back()");
  stl::queue<int> s({1, 2, 3});
  BOOST_CHECK(s.front() == 1);
  BOOST_CHECK(s.back() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_capacity) {
  Log("==> test queue capacity");
  stl::queue<int> s({1, 2, 3});
  BOOST_CHECK(s.empty() == false);
  BOOST_CHECK(s.size() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_push) {
  Log("==> test queue push()");
  stl::queue<int> s;
  BOOST_CHECK(s.empty() == true);
  BOOST_CHECK(s.size() == 0);
  for (int i = 0; i < 5; i++) {
    s.push(i);
    BOOST_CHECK(s.back() == i);
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_emplace) {
  Log("==> test queue emplace()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::queue<Point2d> s({{1, 1},
                         {2, 2},
                         {3, 3}});
  auto p = s.emplace(5, 5);
  BOOST_CHECK(p.x == 5);
  BOOST_CHECK(p.y == 5);
  BOOST_CHECK(s.back().x == 5);
  BOOST_CHECK(s.back().y == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_pop) {
  Log("==> test queue pop()");
  stl::queue<int> s({1, 2, 3});
  for (int i = 0; i < 3; i++) {
    BOOST_CHECK(s.front() == i + 1);
    s.pop();
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(queue_swap) {
  Log("==> test queue swap()");
  stl::queue<int> s1({1, 2, 3});
  stl::queue<int> s2({4, 5, 6});
  BOOST_CHECK(s1.back() == 3);
  BOOST_CHECK(s2.back() == 6);
  s1.swap(s2);
  BOOST_CHECK(s1.back() == 6);
  BOOST_CHECK(s2.back() == 3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_operator) {
  Log("==> test operator ==");
  stl::queue<int> s1({1, 2, 3});
  stl::queue<int> s2({1, 2, 3});
  BOOST_CHECK(s1 == s2);
  Log("==> pass!");
}
