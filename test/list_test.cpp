//
// Created by wjl on 2023/4/17.
//

#include "list.h"
#include <gtest/gtest.h>

TEST(test_list, test_list_init) {
  Log("==> test list constructor");
  stl::list<int> l1;
  EXPECT_EQ(l1.empty(), true);
  stl::list<int> l2(5, 1);
  EXPECT_EQ(l2.size(), 5);
  EXPECT_EQ(l2.front(), 1);
  stl::list<int> l3(3);
  EXPECT_EQ(l3.size(), 3);
  EXPECT_EQ(l3.front(), 0);
  stl::list<int> l4(l2);
  EXPECT_EQ(l2, l4);
  stl::list<int> l5(std::move(l2));
  EXPECT_EQ(l5.size(), 5);
  EXPECT_EQ(l5.front(), 1);
  std::initializer_list<int> ilist{1, 2, 3, 4, 5};
  stl::list<int> l6(ilist);
  EXPECT_EQ(l6.size(), 5);
  EXPECT_EQ(l6.front(), 1);
  EXPECT_EQ(l6.back(), 5);
  Log("==> pass!");
}

TEST(test_list, test_list_operator_equal) {
  Log("==> test list operator =");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2 = l1;
  EXPECT_EQ(l2.size(), 3);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l2.back(), 3);
  stl::list<int> l3 = std::move(l2);
  EXPECT_EQ(l3.size(), 3);
  EXPECT_EQ(l3.front(), 1);
  EXPECT_EQ(l3.back(), 3);
  stl::list<int> l4 = {1, 3, 5};
  EXPECT_EQ(l4.size(), 3);
  EXPECT_EQ(l4.front(), 1);
  EXPECT_EQ(l4.back(), 5);
  Log("==> pass!");
}

TEST(test_list, test_list_assign) {
  Log("==> test list assign()");
  stl::list<int> l{1, 2, 3, 4, 5};
  l.assign(2, 3);
  EXPECT_EQ(l.size(), 2);
  EXPECT_EQ(l.front(), 3);
  EXPECT_EQ(l.back(), 3);
  l.assign(5, 6);
  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 6);
  EXPECT_EQ(l.back(), 6);
  std::initializer_list<int> ilist1{3, 2, 1};
  l.assign(ilist1);
  EXPECT_EQ(l.size(), 3);
  EXPECT_EQ(l.front(), 3);
  EXPECT_EQ(l.back(), 1);
  std::initializer_list<int> ilist2{9, 7, 5, 3, 1};
  l.assign(ilist2);
  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 9);
  EXPECT_EQ(l.back(), 1);
  Log("==> pass!");
}

TEST(test_list, test_list_front_back) {
  Log("==> test list front() back()");
  stl::list<int> l{5, 3, 7};
  EXPECT_EQ(l.front(), 5);
  EXPECT_EQ(l.back(), 7);
  Log("==> pass!");
}

TEST(test_list, test_list_iterator) {
  Log("==> test list iterator");
  stl::list<int> l{1, 2, 3, 4, 5};
  int i = 1;
  for (auto p = l.begin(); p != l.end(); ++p) {
    EXPECT_EQ(*p, i++);
  }
  i = 1;
  for (auto p = l.cbegin(); p != l.cend(); ++p) {
    EXPECT_EQ(*p, i++);
  }
  i = 5;
  for (auto p = l.rbegin(); p != l.rend(); ++p) {
    EXPECT_EQ(*p, i--);
  }
  i = 5;
  for (auto p = l.crbegin(); p != l.crend(); ++p) {
    EXPECT_EQ(*p, i--);
  }
  Log("==> pass!");
}

TEST(test_list, test_list_capacity) {
  Log("==> test list capacity");
  stl::list<int> l;
  EXPECT_EQ(l.empty(), true);
  l = {1, 2};
  EXPECT_EQ(l.empty(), false);
  EXPECT_EQ(l.size(), 2);
  Log("==> pass!");
}

TEST(test_list, test_list_clear) {
  Log("==> test list clear()");
  stl::list<int> l{3, 4, 5};
  EXPECT_EQ(l.size(), 3);
  l.clear();
  EXPECT_EQ(l.empty(), true);
  Log("==> pass!");
}

TEST(test_list, test_list_insert) {
  Log("==> test list insert()");
  stl::list<int> l{2, 3, 4};
  EXPECT_EQ(l.front(), 2);
  l.insert(l.begin(), 4);
  EXPECT_EQ(l.front(), 4);
  int a = 9;
  l.insert(l.begin(), std::move(a));
  EXPECT_EQ(l.front(), 9);
  l.insert(l.begin(), 4, 2);
  EXPECT_EQ(l.size(), 9);
  EXPECT_EQ(l.front(), 2);
  std::initializer_list<int> ilist{9, 8, 7};
  l.insert(l.begin(), ilist);
  EXPECT_EQ(l.size(), 12);
  EXPECT_EQ(l.front(), 9);
  Log("==> pass!");
}

TEST(test_list, test_list_emplace) {
  Log("==> test list emplace()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::list<Point2d> l{
    {1, 1},
    {2, 2},
    {3, 3}};
  l.emplace(l.end(), 5, 5);
  EXPECT_EQ(l.back().x, 5);
  EXPECT_EQ(l.back().y, 5);
  Log("==> pass!");
}

TEST(test_list, test_list_erase) {
  Log("==> test list erase()");
  stl::list<int> l{1, 3, 5, 7, 9};
  EXPECT_EQ(l.back(), 9);
  auto last = l.end();
  last--;
  l.erase(last);
  EXPECT_EQ(l.back(), 7);
  l.erase(l.begin(), l.end());
  EXPECT_EQ(l.empty(), true);
  Log("==> pass!");
}

TEST(test_list, test_list_push_back) {
  Log("==> test list push_back()");
  stl::list<int> l{1, 2, 3};
  for (int i = 0; i < 3; i++) {
    l.push_back(i);
    EXPECT_EQ(l.back(), i);
  }
  int a = 10;
  l.push_back(std::move(a));
  EXPECT_EQ(l.back(), 10);
  Log("==> pass!");
}

TEST(test_list, test_list_emplace_back) {
  Log("==> test list emplace_back()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::list<Point2d> l{
    {1, 1},
    {2, 2},
    {3, 3}};
  auto p = l.emplace_back(5, 5);
  EXPECT_EQ(p.x, 5);
  EXPECT_EQ(p.y, 5);
  EXPECT_EQ(l.back().x, 5);
  EXPECT_EQ(l.back().y, 5);
  Log("==> pass!");
}

TEST(test_list, test_list_pop_back) {
  Log("==> test list pop_back()");
  stl::list<int> l{1, 2, 3};
  EXPECT_EQ(l.back(), 3);
  l.pop_back();
  EXPECT_EQ(l.back(), 2);
  l.pop_back();
  EXPECT_EQ(l.back(), 1);
  l.pop_back();
  EXPECT_EQ(l.empty(), true);
  Log("==> pass!");
}

TEST(test_list, test_list_push_front) {
  Log("==> test list push_front()");
  stl::list<int> l{1, 2, 3};
  for (int i = 1; i <= 3; i++) {
    l.push_front(i);
  }
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.front(), 3);
  int a = 9;
  l.push_front(std::move(a));
  EXPECT_EQ(l.front(), 9);
  Log("==> pass!");
}

TEST(test_list, test_list_emplace_front) {
  Log("==> test list emplace_front()");
  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
  };
  stl::list<Point2d> l{
    {1, 1},
    {2, 2},
    {3, 3}};
  auto p = l.emplace_front(5, 5);
  EXPECT_EQ(p.x, 5);
  EXPECT_EQ(p.y, 5);
  EXPECT_EQ(l.front().x, 5);
  EXPECT_EQ(l.front().y, 5);
  Log("==> pass!");
}

TEST(test_list, test_list_pop_front) {
  Log("==> test list pop_front()");
  stl::list<int> l{1, 2, 3};
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  l.pop_front();
  EXPECT_EQ(l.empty(), true);
  Log("==> pass!");
}

TEST(test_list, test_list_resize) {
  Log("==> test list resize()");
  stl::list<int> l{1, 2, 3};
  EXPECT_EQ(l.size(), 3);
  EXPECT_EQ(l.back(), 3);
  l.resize(2);
  EXPECT_EQ(l.size(), 2);
  EXPECT_EQ(l.back(), 2);
  l.resize(5, 9);
  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 9);
  Log("==> pass!");
}

TEST(test_list, test_list_swap) {
  Log("==> test list swap()");
  stl::list<int> l1{1, 2, 3, 4, 5};
  stl::list<int> l2{6, 7, 8, 9};
  EXPECT_EQ(l1.front(), 1);
  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l2.front(), 6);
  EXPECT_EQ(l2.size(), 4);
  l1.swap(l2);
  EXPECT_EQ(l1.front(), 6);
  EXPECT_EQ(l1.size(), 4);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l2.size(), 5);
  Log("==> pass!");
}

TEST(test_list, test_list_merge) {
  Log("==> test list merge()");
  stl::list<int> l1{1, 3, 5, 7, 9};
  stl::list<int> l2{2, 4, 6, 8, 10};
  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l2.size(), 5);
  l1.merge(l2);
  EXPECT_EQ(l1.back(), 10);
  EXPECT_EQ(l1.size(), 10);
  l1.assign({1, 3, 7});
  stl::list<int> l3{2, 5, 6};
  l1.merge(std::move(l3));
  EXPECT_EQ(l1.size(), 6);
  EXPECT_EQ(l1.back(), 7);

  struct Point2d {
    int x, y;
    Point2d() = default;
    Point2d(int x, int y) : x(x), y(y) {}
    bool operator==(const Point2d &other) {
      return this->x == other.x && this->y == other.y;
    }
  };
  stl::list<Point2d> p1{
    {1, 1},
    {3, 3},
    {5, 5}};
  stl::list<Point2d> p2{
    {2, 2},
    {3, 4},
    {5, 6}};
  p1.merge(p2, [](const Point2d &p1, const Point2d &p2) { return (p1.x + p1.y) < (p2.x + p2.y); });
  EXPECT_EQ(p1.size(), 6);
  Log("==> pass!");
}

TEST(test_list, test_list_splice) {
  Log("==> test list splice()");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2{4, 5, 6};
  l1.splice(l1.begin(), l2);
  EXPECT_EQ(l1.front(), 4);
  EXPECT_EQ(l1.size(), 6);
  l2.assign({7, 8, 9});
  l1.splice(l1.end(), l2, l2.begin());
  EXPECT_EQ(l1.size(), 7);
  EXPECT_EQ(l1.back(), 7);
  EXPECT_EQ(l2.front(), 8);
  EXPECT_EQ(l2.back(), 9);
  l1.splice(l1.end(), l2, l2.begin(), l2.end());
  EXPECT_EQ(l1.size(), 9);
  EXPECT_EQ(l1.back(), 9);
  Log("==> pass!");
}

TEST(test_list, test_list_remove) {
  Log("==> test list remove()");
  stl::list<int> l{1, 1, 4, 5, 1, 4};
  l.remove(1);
  EXPECT_EQ(l.size(), 3);
  l.assign({4, 5, 3, 6, 2, 5, 1});
  l.remove_if([](int n) { return n > 2; });
  EXPECT_EQ(l.size(), 2);
  EXPECT_EQ(l.front(), 2);
  EXPECT_EQ(l.back(), 1);
  Log("==> pass!");
}

TEST(test_list, test_list_reverse) {
  Log("==> test list reverse()");
  stl::list<int> l{1, 1, 4, 5, 1, 4};
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 4);
  l.reverse();
  EXPECT_EQ(l.front(), 4);
  EXPECT_EQ(l.back(), 1);
  Log("==> pass!");
}

TEST(test_list, test_list_unique) {
  Log("==> test list unique()");
  stl::list<int> l{1, 1, 4, 5, 1, 4, 4, 7, 7, 7, 7, 8, 9};
  l.unique();
  EXPECT_EQ(l.size(), 8);
  l.assign({1, 2, 12, 23, 3, 2, 51, 1, 2, 2});
  l.unique([mod = 10](int n, int m) { return (n % mod) == (m % mod); });
  EXPECT_EQ(l.size(), 6);
  Log("==> pass!");
}

TEST(test_list, test_list_sort) {
  Log("==> test list sort()");
  stl::list<int> l{4, 5, 3, 6, 2, 1};
  l.print();
  l.sort();
  l.print();
  Log("==> pass!");
}

TEST(test_list, test_operator_equal_equal) {
  Log("==> test operator ==");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2{4, 5, 6};
  stl::list<int> l3{1, 2, 3};
  EXPECT_NE(l1, l2);
  EXPECT_EQ(l1, l3);
  Log("==> pass!");
}

TEST(test_list, test_erase_if) {
  Log("==> test erase_if()");
  stl::list<char> cnt;
  for (char i = '0'; i <= '9'; i++) {
    cnt.push_back(i);
  }
  EXPECT_EQ(cnt.size(), 10);
  EXPECT_EQ(cnt.back(), '9');
  cnt.print();
  stl::erase(cnt, '3');
  cnt.print();
  EXPECT_EQ(cnt.size(), 9);
  auto erased = stl::erase_if(cnt, [](char x) {
    return (x - '0') % 2 == 0;
  });
  cnt.print();
  EXPECT_EQ(erased, 5);
  Log("==> pass!");
}

TEST(test_list, test_list_print) {
  class Point3d {
  public:
    double x;
    double y;
    double z;
    Point3d() = default;
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3d(Point3d &&other) noexcept : x(other.x), y(other.y), z(other.z) {}
    Point3d &operator=(const Point3d &other) = default;
  };
  stl::list<Point3d> l;
  for (int i = 0; i < 5; i++) {
    double rand = 0.05 * i;
    l.emplace_back(i * rand, (i + 1) * rand, (i + 2) * rand);
  }
  auto lambda = [](const Point3d &p) {
    printf("(%g, %g, %g)\n", p.x, p.y, p.z);
  };
  l.for_each(l.begin(), l.end(), lambda);
  l.for_each(l.cbegin(), l.cend(), lambda);
  l.for_each(l.rbegin(), l.rend(), lambda);
  l.for_each(l.crbegin(), l.crend(), lambda);
  l.print([](const Point3d &p) {
    printf("(%.4g, %.4g, %.4g)", p.x, p.y, p.z);
  });
}
