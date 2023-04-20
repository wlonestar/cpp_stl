//
// Created by wjl on 2023/4/17.
//

#include "list.h"
#include <list>

#include <cassert>

template<class T>
void test_list_init() {
  Log("==> test list constructor");
  stl::list<T> l1;
  l1.print();
  stl::list<T> l2(5, 1);
  l2.print();
  stl::list<T> l3(3);
  l3.print();
  stl::list<T> l4(l2);
  l4.print();
  stl::list<T> l5(std::move(l2));
  l5.print();
  std::initializer_list<T> ilist{1, 2, 3, 4, 5};
  stl::list<T> l6(ilist);
  l6.print();
  Log("==> pass!");
}

template<class T>
void test_list_operator_equal() {
  Log("==> test list operator =");
  stl::list<T> l1{1, 2, 3};
  l1.print();
  stl::list<T> l2 = l1;
  l2.print();
  stl::list<T> l3 = std::move(l2);
  l3.print();
  stl::list<T> l4 = {1, 3, 5};
  l4.print();
  Log("==> pass!");
}

template<class T>
void test_list_assign() {
  Log("==> test list assign()");
  stl::list<T> l{1, 2, 3, 4, 5};
  l.print();
  l.assign(2, 3);
  l.print();
  l.assign(5, 6);
  l.print();
  std::initializer_list<T> ilist1{3, 2, 1};
  l.assign(ilist1);
  l.print();
  std::initializer_list<T> ilist2{9, 7, 5, 3, 1};
  l.assign(ilist2);
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_front_back() {
  Log("==> test list front() back()");
  stl::list<T> l{5, 3, 7};
  auto front = l.front();
  auto back = l.back();
  assert(front == 5);
  assert(back == 7);
  Log("==> pass!");
}

template<class T>
void test_list_iterator() {
  Log("==> test list iterator");
  stl::list<T> l{5, 3, 7, 9};
  for (auto p = l.begin(); p != l.end(); ++p) {
    std::cout << *p << " ";
  }
  std::cout << "\n";
  for (auto p = l.cbegin(); p != l.cend(); ++p) {
    std::cout << *p << " ";
  }
  std::cout << "\n";
  for (auto p = l.rbegin(); p != l.rend(); ++p) {
    std::cout << *p << " ";
  }
  std::cout << "\n";
  for (auto p = l.crbegin(); p != l.crend(); ++p) {
    std::cout << *p << " ";
  }
  std::cout << "\n";
  Log("==> pass!");
}

template<class T>
void test_list_capacity() {
  Log("==> test list capacity");
  stl::list<T> l;
  assert(l.empty() == true);
  l = {1, 2};
  assert(l.empty() == false && l.size() == 2);
  Log("==> pass!");
}

template<class T>
void test_list_clear() {
  Log("==> test list clear()");
  stl::list<T> l{3, 4, 5};
  assert(l.size() == 3);
  l.clear();
  assert(l.empty() == true);
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_insert() {
  Log("==> test list insert()");
  stl::list<T> l{2, 3, 4};
  l.print();
  l.insert(l.begin(), 4);
  T a = 9;
  l.insert(l.begin(), std::move(a));
  l.print();
  l.insert(l.begin(), 4, 2);
  l.print();
  std::initializer_list<T> ilist{9, 8, 7};
  l.insert(l.begin(), ilist);
  l.print();
  Log("==> pass!");
}

void test_list_emplace() {
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
  assert(l.back().x == 5 && l.back().y == 5);
  Log("==> pass!");
}

template<class T>
void test_list_erase() {
  Log("==> test list erase()");
  stl::list<T> l{1, 3, 5, 7, 9};
  l.print();
  auto last = l.end();
  last--;
  l.erase(last);
  l.print();
  l.erase(l.begin(), l.end());
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_push_back() {
  Log("==> test list push_back()");
  stl::list<T> l{1, 2, 3};
  for (int i = 0; i < 3; i++) {
    l.push_back(i);
  }
  T a = 10;
  l.push_back(std::move(a));
  l.print();
  Log("==> pass!");
}

void test_list_emplace_back() {
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
  assert(p.x == 5 && p.y == 5);
  assert(l.back().x == 5 && l.back().y == 5);
  Log("==> pass!");
}

template<class T>
void test_list_pop_back() {
  Log("==> test list pop_back()");
  stl::list<T> l{1, 2, 3};
  assert(l.back() == 3);
  l.pop_back();
  assert(l.back() == 2);
  l.pop_back();
  assert(l.back() == 1);
  l.pop_back();
  assert(l.empty() == true);
  Log("==> pass!");
}

template<class T>
void test_list_push_front() {
  Log("==> test list push_front()");
  stl::list<T> l{1, 2, 3};
  for (int i = 1; i <= 3; i++) {
    l.push_front(i);
  }
  assert(l.size() == 6);
  assert(l.front() == 3);
  T a = 9;
  l.push_front(std::move(a));
  assert(l.front() == 9);
  Log("==> pass!");
}

void test_list_emplace_front() {
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
  assert(p.x == 5 && p.y == 5);
  assert(l.front().x == 5 && l.front().y == 5);
  Log("==> pass!");
}

template<class T>
void test_list_pop_front() {
  Log("==> test list pop_front()");
  stl::list<T> l{1, 2, 3};
  assert(l.front() == 1);
  l.pop_front();
  assert(l.front() == 2);
  l.pop_front();
  assert(l.front() == 3);
  l.pop_front();
  assert(l.empty() == true);
  Log("==> pass!");
}

template<class T>
void test_list_resize() {
  Log("==> test list resize()");
  stl::list<T> l{1, 2, 3};
  assert(l.size() == 3);
  l.print();
  l.resize(2);
  assert(l.size() == 2);
  l.print();
  l.resize(5, 9);
  assert(l.size() == 5);
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_swap() {
  Log("==> test list swap()");
  stl::list<T> l1{1, 2, 3, 4, 5};
  stl::list<T> l2{6, 7, 8, 9};
  assert(l1.front() == 1 && l1.size() == 5);
  assert(l2.front() == 6 && l2.size() == 4);
  l1.swap(l2);
  assert(l1.front() == 6 && l1.size() == 4);
  assert(l2.front() == 1 && l2.size() == 5);
  Log("==> pass!");
}

template<class T>
void test_list_merge() {
  Log("==> test list merge()");
  stl::list<T> l1{1, 2, 3, 4, 5};
  stl::list<T> l2{6, 7, 8, 9};
  l1.print();
  l2.print();
  // TODO
  l1.merge(l2);
  l1.print();
  l2.print();
  Log("==> pass!");
}

template<class T>
void test_list_splice() {
  // TODO
}

template<class T>
void test_list_remove() {
  Log("==> test list remove()");
  stl::list<T> l{1, 1, 4, 5, 1, 4};
  l.remove(1);
  l.print();
  l.assign({4, 5, 3, 6, 2, 5, 1});
  l.remove_if([](int n) { return n > 2; });
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_reverse() {
  Log("==> test list reverse()");
  stl::list<T> l{1, 1, 4, 5, 1, 4};
  l.print();
  l.reverse();
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_unique() {
  Log("==> test list unique()");
  stl::list<T> l{1, 1, 4, 5, 1, 4, 4, 7, 7, 7, 7, 8, 9};
  l.unique();
  assert(l.size() == 8);
  l.print();
  l.assign({1, 2, 12, 23, 3, 2, 51, 1, 2, 2});
  l.print();
  l.unique([mod=10](int n, int m) { return (n % mod) == (m % mod); });
  l.print();
  Log("==> pass!");
}

template<class T>
void test_list_sort() {
  Log("==> test list sort()");
  // TODO
  Log("==> pass!");
}

template<class T>
void test_list() {
  test_list_init<T>();
  test_list_operator_equal<T>();
  test_list_assign<T>();
  test_list_front_back<T>();
  test_list_iterator<T>();
  test_list_capacity<T>();
  test_list_clear<T>();
  test_list_insert<T>();
  test_list_emplace();
  test_list_erase<T>();
  test_list_push_back<T>();
  test_list_emplace_back();
  test_list_pop_back<T>();
  test_list_push_front<T>();
  test_list_emplace_front();
  test_list_pop_front<T>();
  test_list_resize<T>();
  test_list_swap<T>();
  test_list_merge<T>();
  test_list_splice<T>();
  test_list_remove<T>();
  test_list_reverse<T>();
  test_list_unique<T>();
  test_list_sort<T>();
}

int main() {
  test_list<int>();
  return 0;
}
