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
void test_list() {
  test_list_init<T>();
  test_list_operator_equal<T>();
  test_list_assign<T>();
  test_list_front_back<T>();
  test_list_iterator<T>();
  test_list_capacity<T>();
  test_list_clear<T>();
}

int main() {
  test_list<int>();
  return 0;
}
