//
// Created by wjl on 2023/4/25.
//

#include "queue.h"
#include <gtest/gtest.h>

TEST(test_queue, test_queue_init) {
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

TEST(test_queue, test_queue_assignment) {
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

TEST(test_queue, test_queue_front_back) {
  Log("==> test queue front() and back()");
  stl::queue<int> s({1, 2, 3});
  EXPECT_EQ(s.front(), 1);
  EXPECT_EQ(s.back(), 3);
  Log("==> pass!");
}

TEST(test_queue, test_queue_capacity) {
  Log("==> test queue capacity");
  stl::queue<int> s({1, 2, 3});
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 3);
  Log("==> pass!");
}

TEST(test_queue, test_queue_push) {
  Log("==> test queue push()");
  stl::queue<int> s;
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.size(), 0);
  for (int i = 0; i < 5; i++) {
    s.push(i);
    EXPECT_EQ(s.back(), i);
  }
  Log("==> pass!");
}

TEST(test_queue, test_queue_emplace) {
  Log("==> test queue emplace()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::queue<Point2d> s({
    {1, 1},
    {2, 2},
    {3, 3}});
  auto p = s.emplace(5, 5);
  EXPECT_EQ(p.x, 5);
  EXPECT_EQ(p.y, 5);
  EXPECT_EQ(s.back().x, 5);
  EXPECT_EQ(s.back().y, 5);
  Log("==> pass!");
}

TEST(test_queue, test_queue_pop) {
  Log("==> test queue pop()");
  stl::queue<int> s({1, 2, 3});
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(s.front(), i + 1);
    s.pop();
  }
  Log("==> pass!");
}

TEST(test_queue, test_queue_swap) {
  Log("==> test queue swap()");
  stl::queue<int> s1({1, 2, 3});
  stl::queue<int> s2({4, 5, 6});
  EXPECT_EQ(s1.back(), 3);
  EXPECT_EQ(s2.back(), 6);
  s1.swap(s2);
  EXPECT_EQ(s1.back(), 6);
  EXPECT_EQ(s2.back(), 3);
  Log("==> pass!");
}

TEST(test_queue, test_operator) {
  Log("==> test operator ==");
  stl::queue<int> s1({1, 2, 3});
  stl::queue<int> s2({1, 2, 3});
  EXPECT_EQ(s1, s2);
  Log("==> pass!");
}
