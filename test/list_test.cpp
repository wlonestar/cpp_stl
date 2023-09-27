//
// Created by wjl on 2023/4/17.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE list_test
#include <boost/test/included/unit_test.hpp>

#include <list.h>

BOOST_AUTO_TEST_CASE(list_init) {
  Log("==> test list constructor");
  stl::list<int> l1;
  BOOST_CHECK(l1.empty() == true);
  stl::list<int> l2(5, 1);
  BOOST_CHECK(l2.size() == 5);
  BOOST_CHECK(l2.front() == 1);
  stl::list<int> l3(3);
  BOOST_CHECK(l3.size() == 3);
  BOOST_CHECK(l3.front() == 0);
  stl::list<int> l4(l2);
  BOOST_CHECK(l2 == l4);
  stl::list<int> l5(std::move(l2));
  BOOST_CHECK(l5.size() == 5);
  BOOST_CHECK(l5.front() == 1);
  std::initializer_list<int> ilist{1, 2, 3, 4, 5};
  stl::list<int> l6(ilist);
  BOOST_CHECK(l6.size() == 5);
  BOOST_CHECK(l6.front() == 1);
  BOOST_CHECK(l6.back() == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_operator_equal) {
  Log("==> test list operator =");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2 = l1;
  BOOST_CHECK(l2.size() == 3);
  BOOST_CHECK(l2.front() == 1);
  BOOST_CHECK(l2.back() == 3);
  stl::list<int> l3 = std::move(l2);
  BOOST_CHECK(l3.size() == 3);
  BOOST_CHECK(l3.front() == 1);
  BOOST_CHECK(l3.back() == 3);
  stl::list<int> l4 = {1, 3, 5};
  BOOST_CHECK(l4.size() == 3);
  BOOST_CHECK(l4.front() == 1);
  BOOST_CHECK(l4.back() == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_assign) {
  Log("==> test list assign()");
  stl::list<int> l{1, 2, 3, 4, 5};
  l.assign(2, 3);
  BOOST_CHECK(l.size() == 2);
  BOOST_CHECK(l.front() == 3);
  BOOST_CHECK(l.back() == 3);
  l.assign(5, 6);
  BOOST_CHECK(l.size() == 5);
  BOOST_CHECK(l.front() == 6);
  BOOST_CHECK(l.back() == 6);
  std::initializer_list<int> ilist1{3, 2, 1};
  l.assign(ilist1);
  BOOST_CHECK(l.size() == 3);
  BOOST_CHECK(l.front() == 3);
  BOOST_CHECK(l.back() == 1);
  std::initializer_list<int> ilist2{9, 7, 5, 3, 1};
  l.assign(ilist2);
  BOOST_CHECK(l.size() == 5);
  BOOST_CHECK(l.front() == 9);
  BOOST_CHECK(l.back() == 1);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_front_back) {
  Log("==> test list front() back()");
  stl::list<int> l{5, 3, 7};
  BOOST_CHECK(l.front() == 5);
  BOOST_CHECK(l.back() == 7);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_iterator) {
  Log("==> test list iterator");
  stl::list<int> l{1, 2, 3, 4, 5};
  int i = 1;
  for (auto p = l.begin(); p != l.end(); ++p) {
    BOOST_CHECK(*p == i++);
  }
  i = 1;
  for (auto p = l.cbegin(); p != l.cend(); ++p) {
    BOOST_CHECK(*p == i++);
  }
  i = 5;
  for (auto p = l.rbegin(); p != l.rend(); ++p) {
    BOOST_CHECK(*p == i--);
  }
  i = 5;
  for (auto p = l.crbegin(); p != l.crend(); ++p) {
    BOOST_CHECK(*p == i--);
  }
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_capacity) {
  Log("==> test list capacity");
  stl::list<int> l;
  BOOST_CHECK(l.empty() == true);
  l = {1, 2};
  BOOST_CHECK(l.empty() == false);
  BOOST_CHECK(l.size() == 2);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_clear) {
  Log("==> test list clear()");
  stl::list<int> l{3, 4, 5};
  BOOST_CHECK(l.size() == 3);
  l.clear();
  BOOST_CHECK(l.empty() == true);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_insert) {
  Log("==> test list insert()");
  stl::list<int> l{2, 3, 4};
  BOOST_CHECK(l.front() == 2);
  l.insert(l.begin(), 4);
  BOOST_CHECK(l.front() == 4);
  int a = 9;
  l.insert(l.begin(), std::move(a));
  BOOST_CHECK(l.front() == 9);
  l.insert(l.begin(), 4, 2);
  BOOST_CHECK(l.size() == 9);
  BOOST_CHECK(l.front() == 2);
  std::initializer_list<int> ilist{9, 8, 7};
  l.insert(l.begin(), ilist);
  BOOST_CHECK(l.size() == 12);
  BOOST_CHECK(l.front() == 9);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_emplace) {
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
  BOOST_CHECK(l.back().x == 5);
  BOOST_CHECK(l.back().y == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_erase) {
  Log("==> test list erase()");
  stl::list<int> l{1, 3, 5, 7, 9};
  BOOST_CHECK(l.back() == 9);
  auto last = l.end();
  last--;
  l.erase(last);
  BOOST_CHECK(l.back() == 7);
  l.erase(l.begin(), l.end());
  BOOST_CHECK(l.empty() == true);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_push_back) {
  Log("==> test list push_back()");
  stl::list<int> l{1, 2, 3};
  for (int i = 0; i < 3; i++) {
    l.push_back(i);
    BOOST_CHECK(l.back() == i);
  }
  int a = 10;
  l.push_back(std::move(a));
  BOOST_CHECK(l.back() == 10);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_emplace_back) {
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
  BOOST_CHECK(p.x == 5);
  BOOST_CHECK(p.y == 5);
  BOOST_CHECK(l.back().x == 5);
  BOOST_CHECK(l.back().y == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_pop_back) {
  Log("==> test list pop_back()");
  stl::list<int> l{1, 2, 3};
  BOOST_CHECK(l.back() == 3);
  l.pop_back();
  BOOST_CHECK(l.back() == 2);
  l.pop_back();
  BOOST_CHECK(l.back() == 1);
  l.pop_back();
  BOOST_CHECK(l.empty() == true);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_push_front) {
  Log("==> test list push_front()");
  stl::list<int> l{1, 2, 3};
  for (int i = 1; i <= 3; i++) {
    l.push_front(i);
  }
  BOOST_CHECK(l.size() == 6);
  BOOST_CHECK(l.front() == 3);
  int a = 9;
  l.push_front(std::move(a));
  BOOST_CHECK(l.front() == 9);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_emplace_front) {
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
  BOOST_CHECK(p.x == 5);
  BOOST_CHECK(p.y == 5);
  BOOST_CHECK(l.front().x == 5);
  BOOST_CHECK(l.front().y == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_pop_front) {
  Log("==> test list pop_front()");
  stl::list<int> l{1, 2, 3};
  BOOST_CHECK(l.front() == 1);
  l.pop_front();
  BOOST_CHECK(l.front() == 2);
  l.pop_front();
  BOOST_CHECK(l.front() == 3);
  l.pop_front();
  BOOST_CHECK(l.empty() == true);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_resize) {
  Log("==> test list resize()");
  stl::list<int> l{1, 2, 3};
  BOOST_CHECK(l.size() == 3);
  BOOST_CHECK(l.back() == 3);
  l.resize(2);
  BOOST_CHECK(l.size() == 2);
  BOOST_CHECK(l.back() == 2);
  l.resize(5, 9);
  BOOST_CHECK(l.size() == 5);
  BOOST_CHECK(l.front() == 1);
  BOOST_CHECK(l.back() == 9);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_swap) {
  Log("==> test list swap()");
  stl::list<int> l1{1, 2, 3, 4, 5};
  stl::list<int> l2{6, 7, 8, 9};
  BOOST_CHECK(l1.front() == 1);
  BOOST_CHECK(l1.size() == 5);
  BOOST_CHECK(l2.front() == 6);
  BOOST_CHECK(l2.size() == 4);
  l1.swap(l2);
  BOOST_CHECK(l1.front() == 6);
  BOOST_CHECK(l1.size() == 4);
  BOOST_CHECK(l2.front() == 1);
  BOOST_CHECK(l2.size() == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_merge) {
  Log("==> test list merge()");
  stl::list<int> l1{1, 3, 5, 7, 9};
  stl::list<int> l2{2, 4, 6, 8, 10};
  BOOST_CHECK(l1.size() == 5);
  BOOST_CHECK(l2.size() == 5);
  l1.merge(l2);
  BOOST_CHECK(l1.back() == 10);
  BOOST_CHECK(l1.size() == 10);
  l1.assign({1, 3, 7});
  stl::list<int> l3{2, 5, 6};
  l1.merge(std::move(l3));
  BOOST_CHECK(l1.size() == 6);
  BOOST_CHECK(l1.back() == 7);

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
  BOOST_CHECK(p1.size() == 6);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_splice) {
  Log("==> test list splice()");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2{4, 5, 6};
  l1.splice(l1.begin(), l2);
  BOOST_CHECK(l1.front() == 4);
  BOOST_CHECK(l1.size() == 6);
  l2.assign({7, 8, 9});
  l1.splice(l1.end(), l2, l2.begin());
  BOOST_CHECK(l1.size() == 7);
  BOOST_CHECK(l1.back() == 7);
  BOOST_CHECK(l2.front() == 8);
  BOOST_CHECK(l2.back() == 9);
  l1.splice(l1.end(), l2, l2.begin(), l2.end());
  BOOST_CHECK(l1.size() == 9);
  BOOST_CHECK(l1.back() == 9);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_remove) {
  Log("==> test list remove()");
  stl::list<int> l{1, 1, 4, 5, 1, 4};
  l.remove(1);
  BOOST_CHECK(l.size() == 3);
  l.assign({4, 5, 3, 6, 2, 5, 1});
  l.remove_if([](int n) { return n > 2; });
  BOOST_CHECK(l.size() == 2);
  BOOST_CHECK(l.front() == 2);
  BOOST_CHECK(l.back() == 1);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_reverse) {
  Log("==> test list reverse()");
  stl::list<int> l{1, 1, 4, 5, 1, 4};
  BOOST_CHECK(l.front() == 1);
  BOOST_CHECK(l.back() == 4);
  l.reverse();
  BOOST_CHECK(l.front() == 4);
  BOOST_CHECK(l.back() == 1);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_unique) {
  Log("==> test list unique()");
  stl::list<int> l{1, 1, 4, 5, 1, 4, 4, 7, 7, 7, 7, 8, 9};
  l.unique();
  BOOST_CHECK(l.size() == 8);
  l.assign({1, 2, 12, 23, 3, 2, 51, 1, 2, 2});
  l.unique([mod = 10](int n, int m) { return (n % mod) == (m % mod); });
  BOOST_CHECK(l.size() == 6);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_sort) {
  Log("==> test list sort()");
  stl::list<int> l{4, 5, 3, 6, 2, 1};
  l.print();
  l.sort();
  l.print();
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_operator_equal_equal) {
  Log("==> test operator ==");
  stl::list<int> l1{1, 2, 3};
  stl::list<int> l2{4, 5, 6};
  stl::list<int> l3{1, 2, 3};
  BOOST_CHECK(l1 != l2);
  BOOST_CHECK(l1 == l3);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(test_erase_if) {
  Log("==> test erase_if()");
  stl::list<char> cnt;
  for (char i = '0'; i <= '9'; i++) {
    cnt.push_back(i);
  }
  BOOST_CHECK(cnt.size() == 10);
  BOOST_CHECK(cnt.back() == '9');
  cnt.print();
  stl::erase(cnt, '3');
  cnt.print();
  BOOST_CHECK(cnt.size() == 9);
  auto erased = stl::erase_if(cnt, [](char x) {
    return (x - '0') % 2 == 0;
  });
  cnt.print();
  BOOST_CHECK(erased == 5);
  Log("==> pass!");
}

BOOST_AUTO_TEST_CASE(list_print) {
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
