//
// Created by wjl on 2023/4/17.
//

#include "list.h"

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
  Log("==> pass!");
}

template<class T>
void test_list() {
  test_list_init<T>();
  test_list_operator_equal<T>();
}

int main() {
  test_list<int>();
  return 0;
}
